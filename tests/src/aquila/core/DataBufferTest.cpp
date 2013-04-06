#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/core/DataBuffer.h"

using namespace testing;

namespace aquila {
	namespace core {

class DataBufferTest : public ::testing::Test {
protected:
	IDataBuffer* buffer;

	virtual void SetUp() {
		buffer = new DataBuffer(100);
	}

	virtual void TearDown() {
		if ( buffer != 0 ) {
			delete buffer;
		}
	}

};

TEST_F(DataBufferTest, testConstructor) {
	ASSERT_EQ(1, buffer->getRefCount());
}

TEST_F(DataBufferTest, testGetPointer) {
	ASSERT_NE((LPBYTE)0, buffer->getPointer());
	memset(buffer->getPointer(), 0, 100);
}

TEST_F(DataBufferTest, testGetSize) {
	ASSERT_EQ(100, buffer->getSize());
}

	} // end namespace core
} // end namespace aquila