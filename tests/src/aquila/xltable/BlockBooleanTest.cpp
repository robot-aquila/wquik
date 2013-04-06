#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/xltable/BlockBoolean.h"
#include "aquila/xltable/MockCellAggregator.h"
#include "aquila/xltable/MockDataStream.h"

using namespace testing;

namespace aquila {
	namespace xltable {

class BlockBooleanTest : public ::testing::Test {
protected:
	IBlock* block;
	MockDataStream stream;
	MockCellAggregator cells;

	virtual void SetUp() {
		block = new BlockBoolean();
	}

	virtual void TearDown() {
		block->drop();
	}

};

TEST_F(BlockBooleanTest, testConstructor) {
	ASSERT_EQ(1, block->getRefCount());
}

TEST_F(BlockBooleanTest, testReadBlock) {
	{
		InSequence s;
		EXPECT_CALL(stream, readWord())
			.Times(2)
			.WillOnce(Return(sizeof(WORD) * 2)) // размер блока
			.WillOnce(Return(0));
		EXPECT_CALL(cells, addBoolean(false))
			.Times(1)
			.WillOnce(Return(0));
		EXPECT_CALL(stream, readWord())
			.Times(1)
			.WillOnce(Return(1));
		EXPECT_CALL(cells, addBoolean(true))
			.Times(1)
			.WillOnce(Return(1));
	}

	block->readBlock(&stream, &cells);
}

	} // end namespace xltable
} // end namespace aquila
