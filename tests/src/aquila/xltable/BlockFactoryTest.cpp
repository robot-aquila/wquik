#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/xltable/BlockFactory.h"

using namespace testing;

namespace aquila {
	namespace xltable {

class BlockFactoryTest : public ::testing::Test {
protected:
	IBlockFactory* factory;

	virtual void SetUp() {
		factory = new BlockFactory();
	}

	virtual void TearDown() {
		factory->drop();
	}

};

TEST_F(BlockFactoryTest, testConstructor) {
	ASSERT_EQ(1, factory->getRefCount());
}

TEST_F(BlockFactoryTest, testProduceBlockOk) {
	try {
		ASSERT_NE((IBlock*)0, factory->produceBlock(1)); // float
		ASSERT_NE((IBlock*)0, factory->produceBlock(2)); // string
		ASSERT_NE((IBlock*)0, factory->produceBlock(3)); // bool
		ASSERT_NE((IBlock*)0, factory->produceBlock(4)); // error
		ASSERT_NE((IBlock*)0, factory->produceBlock(5)); // blank
		ASSERT_NE((IBlock*)0, factory->produceBlock(6)); // int
		ASSERT_NE((IBlock*)0, factory->produceBlock(7)); // skip
	} catch ( ... ) {
		FAIL() << "Uncaught exception";
	}
}

TEST_F(BlockFactoryTest, testProduceBlockThrowsIfUnknownBlockType) {
	try {
		factory->produceBlock(12345);
		ADD_FAILURE() << "Expected exception: XltException";
	} catch ( XltException e ) {
		ASSERT_EQ((string)"Unknown block type: 12345", e.what());
		SUCCEED();
	} catch ( ... ) {
		FAIL() << "Uncaught exception";
	}
}

	} // end namespace xltable
} // end namespace aquila
