#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/xltable/DataStream.h"
#include "aquila/core/DataBuffer.h"

using namespace std;
using namespace aquila::core;

namespace aquila {
	namespace xltable {

class DataStreamTest : public ::testing::Test {
protected:
	IDataBuffer* buffer;
	IDataStream* stream;
	LPBYTE streamData;

	virtual void SetUp() {
		buffer = new DataBuffer(10);
		stream = 0;
		streamData = 0;
	}

	virtual void TearDown() {
		if ( stream != 0 ) {
			stream->drop();
		}
		if ( streamData != 0 ) {
			delete[] streamData;
		}
		delete buffer;
	}

	void allocateBuffer(unsigned int size) {
		if ( streamData != 0 ) {
			FAIL() << "The buffer already in use";
		}
		streamData = new BYTE[size];
	}

};

TEST_F(DataStreamTest, testConstructor_FromPtrAndSize) {
	allocateBuffer(10);
	stream = new DataStream(streamData, 10);
	ASSERT_EQ(1, stream->getRefCount());
	ASSERT_EQ(10, stream->getLength());
	ASSERT_EQ(0, stream->getOffset());
}

TEST_F(DataStreamTest, testConstructor_FromDataBuffer) {
	stream = new DataStream(buffer);
	ASSERT_EQ(2, buffer->getRefCount());
	ASSERT_EQ(1, stream->getRefCount());
	ASSERT_EQ(10, stream->getLength());
	ASSERT_EQ(0, stream->getOffset());
	LPBYTE b = buffer->getPointer();
	b[0] = 1; b[1] = 2; b[2] = 3;
	ASSERT_EQ(1, stream->readByte());
	ASSERT_EQ(2, stream->readByte());
	ASSERT_EQ(3, stream->readByte());
}

TEST_F(DataStreamTest, testReadByte) {
	allocateBuffer(2 * sizeof(BYTE));
	LPBYTE buffer = streamData;
	buffer[0] = 128;
	buffer[1] = 255;

	stream = new DataStream(streamData, 2 * sizeof(BYTE));

	ASSERT_EQ((BYTE)128, stream->readByte());
	ASSERT_EQ(1, stream->getOffset());

	ASSERT_EQ((BYTE)255, stream->readByte());
	ASSERT_EQ(2, stream->getOffset());

	// чтение за пределами буффера
	ASSERT_EQ((BYTE)0, stream->readByte());
	ASSERT_EQ((WORD)0, stream->readWord());
	ASSERT_EQ((DWORD)0, stream->readDword());
	ASSERT_EQ("", stream->readString(123));
	ASSERT_EQ((double)0.0, stream->readFloat());
}

TEST_F(DataStreamTest, testReadWord) {
	allocateBuffer(2 * sizeof(WORD));
	LPWORD buffer = (LPWORD)streamData;
	buffer[0] = 32445;
	buffer[1] = 112;

	stream = new DataStream(streamData, 2 * sizeof(WORD));

	ASSERT_EQ((WORD)32445, stream->readWord());
	ASSERT_EQ(2, stream->getOffset());

	ASSERT_EQ((WORD)112, stream->readWord());
	ASSERT_EQ(4, stream->getOffset());

	// чтение за пределами буффера
	ASSERT_EQ((BYTE)0, stream->readByte());
	ASSERT_EQ((WORD)0, stream->readWord());
	ASSERT_EQ((DWORD)0, stream->readDword());
	ASSERT_EQ("", stream->readString(123));
	ASSERT_EQ((double)0.0, stream->readFloat());
}

TEST_F(DataStreamTest, testReadDword) {
	allocateBuffer(2 * sizeof(DWORD));
	LPDWORD buffer = (LPDWORD)streamData;
	buffer[0] = 3244566;
	buffer[1] = 123112;

	stream = new DataStream(streamData, 2 * sizeof(DWORD));

	ASSERT_EQ((DWORD)3244566, stream->readDword());
	ASSERT_EQ(4, stream->getOffset());

	ASSERT_EQ((DWORD)123112, stream->readDword());
	ASSERT_EQ(8, stream->getOffset());

	// чтение за пределами буффера
	ASSERT_EQ((BYTE)0, stream->readByte());
	ASSERT_EQ((WORD)0, stream->readWord());
	ASSERT_EQ((DWORD)0, stream->readDword());
	ASSERT_EQ("", stream->readString(123));
	ASSERT_EQ((double)0.0, stream->readFloat());
}

TEST_F(DataStreamTest, testReadString) {
	allocateBuffer(12);
	memcpy(streamData, "zulu4", 5);
	memcpy(streamData + 5, "charlie", 7);

	string s;
	stream = new DataStream(streamData, 12);

	s.clear();
	s.append(stream->readString(5), 5);
	ASSERT_EQ((string)"zulu4", s);
	ASSERT_EQ(5, stream->getOffset());

	s.clear();
	s.append(stream->readString(7), 7);
	ASSERT_EQ((string)"charlie", s);
	ASSERT_EQ(12, stream->getOffset());

	// чтение за пределами буффера
	ASSERT_EQ((BYTE)0, stream->readByte());
	ASSERT_EQ((WORD)0, stream->readWord());
	ASSERT_EQ((DWORD)0, stream->readDword());
	ASSERT_EQ("", stream->readString(123));
	ASSERT_EQ((double)0.0, stream->readFloat());
}

TEST_F(DataStreamTest, testReadFloat) {
	allocateBuffer(16);
	double* buffer = (double*)streamData;
	buffer[0] = 324.1123;
	buffer[1] = 123.112;

	stream = new DataStream(streamData, 2 * sizeof(double));

	ASSERT_EQ((double)324.1123, stream->readFloat());
	ASSERT_EQ(8, stream->getOffset());

	ASSERT_EQ((double)123.112, stream->readFloat());
	ASSERT_EQ(16, stream->getOffset());

	// чтение за пределами буффера
	ASSERT_EQ((BYTE)0, stream->readByte());
	ASSERT_EQ((WORD)0, stream->readWord());
	ASSERT_EQ((DWORD)0, stream->readDword());
	ASSERT_EQ("", stream->readString(123));
	ASSERT_EQ((double)0.0, stream->readFloat());
}

	} // end namespace xltable
} // end namespace aquila
