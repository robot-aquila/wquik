#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/xltable/CellBoolean.h"

namespace aquila {
	namespace xltable {

class CellBooleanTest : public ::testing::Test {
protected:
	ICell* cell1;
	ICell* cell2;

	virtual void SetUp() {
		cell1 = new CellBoolean(true);
		cell2 = new CellBoolean(false);
	}

	virtual void TearDown() {
		cell1->drop();
		cell2->drop();
	}

};

TEST_F(CellBooleanTest, testMainType) {
	ASSERT_EQ(1, cell1->getRefCount());
	ASSERT_EQ(true, cell1->isBoolean());
	ASSERT_EQ(true, cell1->asBoolean());
	ASSERT_EQ(1, cell2->getRefCount());
	ASSERT_EQ(true, cell2->isBoolean());
	ASSERT_EQ(false, cell2->asBoolean());
}

TEST_F(CellBooleanTest, testAnotherTypes) {
	ASSERT_EQ(false, cell1->isFloat());
	ASSERT_EQ(0.0, cell1->asFloat());

	ASSERT_EQ(false, cell1->isString());
	ASSERT_EQ("", cell1->asString());

	ASSERT_EQ(false, cell1->isInteger());
	ASSERT_EQ(0, cell1->asInteger());

	ASSERT_EQ(false, cell1->isError());
	ASSERT_EQ(false, cell1->isBlank());
	ASSERT_EQ(false, cell1->isSkip());
}

	} // end namespace xltable
} // end namespace aquila
