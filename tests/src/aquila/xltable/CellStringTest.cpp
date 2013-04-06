#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/xltable/CellString.h"

namespace aquila {
	namespace xltable {

class CellStringTest : public ::testing::Test {
protected:
	ICell* cell;

	virtual void SetUp() {
		cell = new CellString("foobar test", 6);
	}

	virtual void TearDown() {
		cell->drop();
	}

};

TEST_F(CellStringTest, testMainType) {
	ASSERT_EQ(1, cell->getRefCount());
	ASSERT_EQ(true, cell->isString());
	ASSERT_EQ("foobar", cell->asString());
}

TEST_F(CellStringTest, testAnotherTypes) {
	ASSERT_EQ(false, cell->isBoolean());
	ASSERT_EQ(false, cell->asBoolean());

	ASSERT_EQ(false, cell->isFloat());
	ASSERT_EQ(0.0, cell->asFloat());

	ASSERT_EQ(false, cell->isInteger());
	ASSERT_EQ(0, cell->asInteger());

	ASSERT_EQ(false, cell->isError());
	ASSERT_EQ(false, cell->isBlank());
	ASSERT_EQ(false, cell->isSkip());
}

	} // end namespace xltable
} // end namespace aquila
