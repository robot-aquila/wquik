#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/xltable/BlockError.h"
#include "aquila/xltable/MockCellAggregator.h"
#include "aquila/xltable/MockDataStream.h"

using namespace testing;

namespace aquila {
	namespace xltable {

class BlockErrorTest : public ::testing::Test {
protected:
	IBlock* block;
	MockDataStream stream;
	MockCellAggregator cells;

	virtual void SetUp() {
		block = new BlockError();
	}

	virtual void TearDown() {
		block->drop();
	}

};

TEST_F(BlockErrorTest, testConstructor) {
	ASSERT_EQ(1, block->getRefCount());
}

TEST_F(BlockErrorTest, testReadBlock) {
	{
		InSequence s;
		EXPECT_CALL(stream, readWord())
			.Times(2)
			.WillOnce(Return(sizeof(WORD) * 2)) // размер блока
			.WillOnce(Return(7));
		EXPECT_CALL(cells, addError())
			.Times(1);
		EXPECT_CALL(stream, readWord())
			.Times(1)
			.WillOnce(Return(15));
		EXPECT_CALL(cells, addError())
			.Times(1);
	}

	block->readBlock(&stream, &cells);
}

	} // end namespace xltable
} // end namespace aquila
