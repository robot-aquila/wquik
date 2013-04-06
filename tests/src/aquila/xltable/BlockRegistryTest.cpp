#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/xltable/BlockRegistry.h"
#include "aquila/xltable/BlockInteger.h"
#include "aquila/xltable/MockBlockFactory.h"

using namespace testing;

namespace aquila {
	namespace xltable {

class BlockRegistryTest : public ::testing::Test {
protected:
	MockBlockFactory factory;
	IBlockFactory* registry;
	IBlock* block;
	IBlock* secondBlock;


	virtual void SetUp() {
		registry = new BlockRegistry(&factory);
		block = new BlockInteger();
		block->grab();
		secondBlock = new BlockInteger();
		secondBlock->grab();
	}

	virtual void TearDown() {
		if ( registry != 0 ) {
			registry->drop();
		}
		delete block;
		delete secondBlock;
	}

};

TEST_F(BlockRegistryTest, testConstructor) {
	ASSERT_EQ(1, registry->getRefCount());
	ASSERT_EQ(2, factory.getRefCount());
}

TEST_F(BlockRegistryTest, testProduce_Caching) {
	EXPECT_CALL(factory, produceBlock(1))
		.Times(1)
		.WillOnce(Return(block));

	ASSERT_EQ((IBlock*)block, registry->produceBlock(1));
	ASSERT_EQ(2, block->getRefCount()); // счетчик не увеличивает

	// последующие вызовы - результат из кеша
	ASSERT_EQ((IBlock*)block, registry->produceBlock(1));
	ASSERT_EQ(2, block->getRefCount()); // счетчик не увеличивает
}

TEST_F(BlockRegistryTest, testDestructor_DropsFactory) {
	registry->drop();
	registry = 0;
	ASSERT_EQ(1, factory.getRefCount()); // счетчик уменьшен
}

TEST_F(BlockRegistryTest, test_Destructor_DropsCachedBlocks) {
	EXPECT_CALL(factory, produceBlock(1))
		.Times(1)
		.WillOnce(Return(block));
	EXPECT_CALL(factory, produceBlock(2))
		.Times(1)
		.WillOnce(Return(secondBlock));

	registry->produceBlock(1);
	registry->produceBlock(2);

	ASSERT_EQ(2, block->getRefCount()); // счетчики неизменны
	ASSERT_EQ(2, secondBlock->getRefCount());

	registry->drop();
	registry = 0;

	// удаляет закешированные объекты
	ASSERT_EQ(1, block->getRefCount());
	ASSERT_EQ(1, secondBlock->getRefCount());
}

	} // end namespace xltable
} // end namespace aquila
