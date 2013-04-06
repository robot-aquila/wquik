#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/xltable/BlockString.h"
#include "aquila/xltable/MockCellAggregator.h"
#include "aquila/xltable/MockDataStream.h"

using namespace testing;

namespace aquila {
	namespace xltable {

class BlockStringTest : public ::testing::Test {
protected:
	IBlock* block;
	MockDataStream stream;
	MockCellAggregator cells;

	virtual void SetUp() {
		block = new BlockString();
	}

	virtual void TearDown() {
		block->drop();
	}

};

TEST_F(BlockStringTest, testConstructor) {
	ASSERT_EQ(1, block->getRefCount());
}

TEST_F(BlockStringTest, testReadBlock) {
	//"zulu4"   5 + 1 = 6
	//"charlie" 7 + 1 = 8 = 14
	{
		InSequence s;
		EXPECT_CALL(stream, readWord())
			.Times(1)
			.WillOnce(Return(14)); // длина блока
		EXPECT_CALL(stream, readByte())
			.Times(1)
			.WillOnce(Return(5)); // длина строка №1
		EXPECT_CALL(stream, readString(5))
			.Times(1)
			.WillOnce(Return((const char*)"zulu4"));
		EXPECT_CALL(cells, addString((const char*)"zulu4", 5))
			.Times(1)
			.WillOnce(Return(0));
		EXPECT_CALL(stream, readByte())
			.Times(1)
			.WillOnce(Return(7)); // длина строка №2
		EXPECT_CALL(stream, readString(7))
			.Times(1)
			.WillOnce(Return((const char*)"charlie"));
		EXPECT_CALL(cells, addString((const char*)"charlie", 7))
			.Times(1)
			.WillOnce(Return(1));
	}

	block->readBlock(&stream, &cells);
}

	} // end namespace xltable
} // end namespace aquila
