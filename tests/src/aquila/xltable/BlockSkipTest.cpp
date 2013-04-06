#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/xltable/BlockSkip.h"
#include "aquila/xltable/MockCellAggregator.h"
#include "aquila/xltable/MockDataStream.h"

using namespace testing;

namespace aquila {
	namespace xltable {

class BlockSkipTest : public ::testing::Test {
protected:
	IBlock* block;
	MockDataStream stream;
	MockCellAggregator cells;

	virtual void SetUp() {
		block = new BlockSkip();
	}

	virtual void TearDown() {
		block->drop();
	}

};

TEST_F(BlockSkipTest, testConstructor) {
	ASSERT_EQ(1, block->getRefCount());
}

TEST_F(BlockSkipTest, testReadBlock) {
	{
		InSequence s;
		EXPECT_CALL(stream, readWord())
			.Times(2)
			.WillOnce(Return(2)) // размер всегда 2
			.WillOnce(Return(3)); // количество пропущенных ячеек
		EXPECT_CALL(cells, addSkip())
			.Times(3);
	}

	block->readBlock(&stream, &cells);
}

	} // end namespace xltable
} // end namespace aquila
