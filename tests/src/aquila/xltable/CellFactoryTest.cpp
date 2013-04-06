#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/xltable/CellFactory.h"

namespace aquila {
	namespace xltable {

class CellFactoryTest : public ::testing::Test {
protected:
	ICellFactory* factory;
	ICell* cell;

	virtual void SetUp() {
		factory = new CellFactory();
		cell = 0;
	}

	virtual void TearDown() {
		factory->drop();
		if ( cell != 0 ) {
			cell->drop();
		}
	}

};

TEST_F(CellFactoryTest, testCreateFloat) {
	cell = factory->createFloat(654.321);
	ASSERT_NE((ICell*)0, cell);
	ASSERT_EQ(1, cell->getRefCount());
	ASSERT_EQ(true, cell->isFloat());
	ASSERT_EQ(654.321, cell->asFloat());
}

TEST_F(CellFactoryTest, testCreateBoolean) {
	cell = factory->createBoolean(true);
	ASSERT_NE((ICell*)0, cell);
	ASSERT_EQ(1, cell->getRefCount());
	ASSERT_EQ(true, cell->isBoolean());
	ASSERT_EQ(true, cell->asBoolean());
}

TEST_F(CellFactoryTest, testCreateString) {
	cell = factory->createString("zulu4 charlie", 5);
	ASSERT_NE((ICell*)0, cell);
	ASSERT_EQ(1, cell->getRefCount());
	ASSERT_EQ(true, cell->isString());
	ASSERT_EQ("zulu4", cell->asString());
}

TEST_F(CellFactoryTest, testCreateInteger) {
	cell = factory->createInteger(12345);
	ASSERT_NE((ICell*)0, cell);
	ASSERT_EQ(1, cell->getRefCount());
	ASSERT_EQ(true, cell->isInteger());
	ASSERT_EQ(12345, cell->asInteger());
}

TEST_F(CellFactoryTest, testCreateError) {
	cell = factory->createError();
	ASSERT_NE((ICell*)0, cell);
	ASSERT_EQ(1, cell->getRefCount());
	ASSERT_EQ(true, cell->isError());
}

TEST_F(CellFactoryTest, testCreateBlank) {
	cell = factory->createBlank();
	ASSERT_NE((ICell*)0, cell);
	ASSERT_EQ(1, cell->getRefCount());
	ASSERT_EQ(true, cell->isBlank());
}

TEST_F(CellFactoryTest, testCreateSkip) {
	cell = factory->createSkip();
	ASSERT_NE((ICell*)0, cell);
	ASSERT_EQ(1, cell->getRefCount());
	ASSERT_EQ(true, cell->isSkip());
}

	} // end namespace xltable
} // end namespace aquila
