#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/xltable/BlockInteger.h"
#include "aquila/xltable/MockCellAggregator.h"
#include "aquila/xltable/MockDataStream.h"

using namespace testing;

namespace aquila {
	namespace xltable {

class BlockIntegerTest : public ::testing::Test {
protected:
	IBlock* block;
	MockDataStream stream;
	MockCellAggregator cells;

	virtual void SetUp() {
		block = new BlockInteger();
	}

	virtual void TearDown() {
		block->drop();
	}

};

TEST_F(BlockIntegerTest, testConstructor) {
	ASSERT_EQ(1, block->getRefCount());
}

TEST_F(BlockIntegerTest, testReadBlock) {
	{
		InSequence s;
		EXPECT_CALL(stream, readWord())
			.Times(2)
			.WillOnce(Return(sizeof(WORD) * 2)) // размер блока
			.WillOnce(Return(8812));
		EXPECT_CALL(cells, addInteger(8812))
			.Times(1)
			.WillOnce(Return(0));
		EXPECT_CALL(stream, readWord())
			.Times(1)
			.WillOnce(Return(9245));
		EXPECT_CALL(cells, addInteger(9245))
			.Times(1)
			.WillOnce(Return(1));
	}

	block->readBlock(&stream, &cells);
}

	} // end namespace xltable
} // end namespace aquila
