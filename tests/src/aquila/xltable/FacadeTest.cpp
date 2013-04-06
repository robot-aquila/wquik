#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/xltable/Facade.h"
#include "aquila/core/auto_drop.h"
#include "aquila/core/DataBuffer.h"

using namespace testing;
using namespace aquila::core;

namespace aquila {
	namespace xltable {

#define ASSERT_CELL_FLOAT(row, col, value) \
	cell = table->getCell(row, col); \
	ASSERT_TRUE(cell->isFloat()); \
	ASSERT_EQ(value, cell->asFloat())

#define ASSERT_CELL_STRING(row, col, value) \
	cell = table->getCell(row, col); \
	ASSERT_TRUE(cell->isString()); \
	ASSERT_EQ((string)value, cell->asString())

#define ASSERT_CELL_BOOLEAN(row, col, value) \
	cell = table->getCell(row, col); \
	ASSERT_TRUE(cell->isBoolean()); \
	ASSERT_EQ(value, cell->asBoolean())

#define ASSERT_CELL_ERROR(row, col) \
	cell = table->getCell(row, col); \
	ASSERT_TRUE(cell->isError())

#define ASSERT_CELL_BLANK(row, col) \
	cell = table->getCell(row, col); \
	ASSERT_TRUE(cell->isBlank())
		
#define ASSERT_CELL_INTEGER(row, col, value) \
	cell = table->getCell(row, col); \
	ASSERT_TRUE(cell->isInteger()); \
	ASSERT_EQ(value, cell->asInteger())
		
#define ASSERT_CELL_SKIP(row, col) \
	cell = table->getCell(row, col); \
	ASSERT_TRUE(cell->isSkip())

BYTE streamData[] = {
	10,  0, // tdtTable
	 4,  0, // size: always 4 bytes
	 5,  0,	// rows
	 4,  0,	// cols
	 1,  0,	// type float
	16,  0,	// size: 2 x float = 16
	 0,0,0,0,0,0,0,0,						// r1 c1
	 0,0,0,0,0,0,0,0,						// r1 c2
	 2,  0, // type string
	14,  0, // size: 5 + 7 + 2 = 14 bytes
	 5, 'z', 'u', 'l', 'u', '4',			// r1 c3
	 7, 'c', 'h', 'a', 'r', 'l', 'i', 'e',	// r1 c4
	 3,  0, // type boolean
	 4,  0, // size: 2 x bool = 4 bytes
	 1,  0,									// r2 c1
	 0,  0,									// r2 c2
	 4,  0, // type error
	 6,  0, // size: 3 x error = 6 bytes
	 1,  0,									// r2 c3
	 2,  0,									// r2 c4
	 1,	 0,									// r3 c1
	 5,  0, // type blank
	 2,  0, // size: always 2 bytes
	 2,  0,									// r3 c2:c3
	 6,  0, // type integer
	 4,  0, // size: 2 x integer = 4 bytes
    12,  0,									// r3 c4
	 0,  1,									// r4 c1
	 7,  0, // type skip
	 2,  0, // size: always 2 bytes
	 7,  0									// r4 c2:c4, r5:c1:c4
};

class FacadeTest : public ::testing::Test {
protected:
	IFacade* facade;
	IDataStream* stream;
	ITableRange* table;
	char* topic;
	char* item;

	virtual void SetUp() {
		double* buffer = (double*)&streamData[12];
		buffer[0] = 123.456;
		buffer[1] = 654.321;

		topic = "topic";
		item = "item";
		facade = new Facade();
		stream = 0;
		table = 0;
	}

	virtual void TearDown() {
		if ( table != 0 ) {
			table->drop();
		}
		if ( stream != 0 ) {
			stream->drop();
		}
		facade->drop();
	}

	void ASSERT_STREAM() {
		string s;
		ASSERT_NE((IDataStream*)0, stream);
		ASSERT_EQ(10, stream->readWord());
		ASSERT_EQ(4, stream->readWord());
		ASSERT_EQ(5, stream->readWord()); // rows
		ASSERT_EQ(4, stream->readWord()); // cols
		ASSERT_EQ(1, stream->readWord());
		ASSERT_EQ(16, stream->readWord());
		ASSERT_EQ(123.456, stream->readFloat());
		ASSERT_EQ(654.321, stream->readFloat());
		ASSERT_EQ(2, stream->readWord());
		ASSERT_EQ(14, stream->readWord());

		ASSERT_EQ(5, stream->readByte());
		s.clear();
		s.append(stream->readString(5), 5);
		ASSERT_EQ((string)"zulu4", s);
		
		ASSERT_EQ(7, stream->readByte());
		s.clear();
		s.append(stream->readString(7), 7);
		ASSERT_EQ((string)"charlie", s);
		// etc...
	}

};

TEST_F(FacadeTest, testConstructor) {
	ASSERT_EQ(1, facade->getRefCount());
}

TEST_F(FacadeTest, testCreateStream_FromPtrAndSize) {
	stream = facade->createStream(&streamData[0], sizeof(streamData));
	ASSERT_STREAM();
}

TEST_F(FacadeTest, testCreateStream_FromDataBuffer) {
	auto_drop<IDataBuffer> dataBuffer(new DataBuffer(sizeof(streamData)));
	memcpy(dataBuffer->getPointer(), streamData, sizeof(streamData));
	stream = facade->createStream(dataBuffer.get());
	ASSERT_STREAM();
}

TEST_F(FacadeTest, testReadTable) {
	ICell* cell;
	stream = facade->createStream(&streamData[0], sizeof(streamData));
	try {
		table = facade->readTable(topic, item, stream);
		ASSERT_NE((ITableRange*)0, table);

		ASSERT_EQ((string)"topic", table->getTopic());
		ASSERT_EQ((string)"item", table->getItem());
		ASSERT_EQ(5, table->getRows());
		ASSERT_EQ(4, table->getCols());

		ASSERT_CELL_FLOAT(0, 0, 123.456);
		ASSERT_CELL_FLOAT(0, 1, 654.321);
		ASSERT_CELL_STRING(0, 2, "zulu4");
		ASSERT_CELL_STRING(0, 3, "charlie");
		ASSERT_CELL_BOOLEAN(1, 0, true);
		ASSERT_CELL_BOOLEAN(1, 1, false);
		ASSERT_CELL_ERROR(1, 2);
		ASSERT_CELL_ERROR(1, 3);
		ASSERT_CELL_ERROR(2, 0);
		ASSERT_CELL_BLANK(2, 1);
		ASSERT_CELL_BLANK(2, 2);
		ASSERT_CELL_INTEGER(2, 3, 12);
		ASSERT_CELL_INTEGER(3, 0, 256);
		ASSERT_CELL_SKIP(3, 1);
		ASSERT_CELL_SKIP(3, 2);
		ASSERT_CELL_SKIP(3, 3);
		ASSERT_CELL_SKIP(4, 0);
		ASSERT_CELL_SKIP(4, 1);
		ASSERT_CELL_SKIP(4, 2);
		ASSERT_CELL_SKIP(4, 3);

	} catch ( std::exception &e ) {
		FAIL() << "Uncaught exception: " << e.what();
	} catch ( ... ) {
		FAIL() << "Uncaught exception";
	}
}

	} // end namespace xltable
} // end namespace aquila
