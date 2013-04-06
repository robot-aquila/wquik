#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/xltable/BlockBlank.h"
#include "aquila/xltable/MockCellAggregator.h"
#include "aquila/xltable/MockDataStream.h"

using namespace testing;

namespace aquila {
	namespace xltable {

class BlockBlankTest : public ::testing::Test {
protected:
	IBlock* block;
	MockDataStream stream;
	MockCellAggregator cells;

	virtual void SetUp() {
		block = new BlockBlank();
	}

	virtual void TearDown() {
		block->drop();
	}

};

TEST_F(BlockBlankTest, testConstructor) {
	ASSERT_EQ(1, block->getRefCount());
}

TEST_F(BlockBlankTest, testReadBlock) {
	{
		InSequence s;
		EXPECT_CALL(stream, readWord())
			.Times(2)
			.WillOnce(Return(2)) // размер всегда 2
			.WillOnce(Return(4)); // количество пустых полей

		EXPECT_CALL(cells, addBlank()).Times(4);
	}

	block->readBlock(&stream, &cells);
}

	} // end namespace xltable
} // end namespace aquila
