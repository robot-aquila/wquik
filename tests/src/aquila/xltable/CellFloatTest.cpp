#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/xltable/CellFloat.h"

namespace aquila {
	namespace xltable {

class CellFloatTest : public ::testing::Test {
protected:
	CellFloat* cell;

	virtual void SetUp() {
		cell = new CellFloat(123.456);
	}

	virtual void TearDown() {
		cell->drop();
	}

};

TEST_F(CellFloatTest, testMainType) {
	ASSERT_EQ(1, cell->getRefCount());
	ASSERT_EQ(true, cell->isFloat());
	ASSERT_EQ(123.456, cell->asFloat());
}

TEST_F(CellFloatTest, testAnotherTypes) {
	ASSERT_EQ(false, cell->isBoolean());
	ASSERT_EQ(false, cell->asBoolean());

	ASSERT_EQ(false, cell->isString());
	ASSERT_EQ("", cell->asString());

	ASSERT_EQ(false, cell->isInteger());
	ASSERT_EQ(0, cell->asInteger());

	ASSERT_EQ(false, cell->isError());
	ASSERT_EQ(false, cell->isBlank());
	ASSERT_EQ(false, cell->isSkip());
}

	} // end namespace xltable
} // end namespace aquila
