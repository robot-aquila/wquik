#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/xltable/BlockFloat.h"
#include "aquila/xltable/MockCellAggregator.h"
#include "aquila/xltable/MockDataStream.h"

using namespace testing;

namespace aquila {
	namespace xltable {

class BlockFloatTest : public ::testing::Test {
protected:
	IBlock* block;
	MockDataStream stream;
	MockCellAggregator cells;

	virtual void SetUp() {
		block = new BlockFloat();
	}

	virtual void TearDown() {
		block->drop();
	}

};

TEST_F(BlockFloatTest, testConstructor) {
	ASSERT_EQ(1, block->getRefCount());
}

TEST_F(BlockFloatTest, testReadBlock) {
	{
		InSequence s;
		EXPECT_CALL(stream, readWord())
			.Times(1)
			.WillOnce(Return(sizeof(double) * 2)); // размер блока
		EXPECT_CALL(stream, readFloat())
			.Times(1)
			.WillOnce(Return(123.456));
		EXPECT_CALL(cells, addFloat(123.456))
			.Times(1)
			.WillOnce(Return(0));
		EXPECT_CALL(stream, readFloat())
			.Times(1)
			.WillOnce(Return(789.012));
		EXPECT_CALL(cells, addFloat(789.012))
			.Times(1)
			.WillOnce(Return(1));
	}

	block->readBlock(&stream, &cells);
}

	} // end namespace xltable
} // end namespace aquila
