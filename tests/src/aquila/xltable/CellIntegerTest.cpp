#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/xltable/CellInteger.h"

namespace aquila {
	namespace xltable {

class CellIntegerTest : public ::testing::Test {
protected:
	ICell* cell;

	virtual void SetUp() {
		cell = new CellInteger(123456);
	}

	virtual void TearDown() {
		cell->drop();
	}

};

TEST_F(CellIntegerTest, testMainType) {
	ASSERT_EQ(1, cell->getRefCount());
	ASSERT_EQ(true, cell->isInteger());
	ASSERT_EQ(123456, cell->asInteger());
}

TEST_F(CellIntegerTest, testAnotherTypes) {
	ASSERT_EQ(false, cell->isBoolean());
	ASSERT_EQ(false, cell->asBoolean());

	ASSERT_EQ(false, cell->isString());
	ASSERT_EQ("", cell->asString());

	ASSERT_EQ(false, cell->isFloat());
	ASSERT_EQ(0.0, cell->asFloat());

	ASSERT_EQ(false, cell->isError());
	ASSERT_EQ(false, cell->isBlank());
	ASSERT_EQ(false, cell->isSkip());
}

	} // end namespace xltable
} // end namespace aquila
