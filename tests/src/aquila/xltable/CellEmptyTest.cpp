#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/xltable/CellEmpty.h"

namespace aquila {
	namespace xltable {

class CellEmptyTest : public ::testing::Test {
protected:
	ICell *cellBlank;
	ICell *cellSkip;
	ICell *cellError;

	virtual void SetUp() {
		cellBlank = new CellEmpty(CELL_TYPE_BLANK);
		cellSkip = new CellEmpty(CELL_TYPE_SKIP);
		cellError = new CellEmpty(CELL_TYPE_ERROR);
	}

	virtual void TearDown() {
		cellBlank->drop();
		cellSkip->drop();
		cellError->drop();
	}

};

TEST_F(CellEmptyTest, testErrorType) {
	ASSERT_EQ(1, cellError->getRefCount());
	ASSERT_EQ(true, cellError->isError());

	ASSERT_EQ(false, cellError->isBlank());
	ASSERT_EQ(false, cellError->isBoolean());
	ASSERT_EQ(false, cellError->isFloat());
	ASSERT_EQ(false, cellError->isSkip());
	ASSERT_EQ(false, cellError->isString());
	ASSERT_EQ(false, cellError->isInteger());

	ASSERT_EQ("", cellError->asString());
	ASSERT_EQ(0, cellError->asInteger());
	ASSERT_EQ(false, cellError->asBoolean());
	ASSERT_EQ(0.0, cellError->asFloat());
}

TEST_F(CellEmptyTest, testBlankType) {
	ASSERT_EQ(1, cellBlank->getRefCount());
	ASSERT_EQ(true, cellBlank->isBlank());

	ASSERT_EQ(false, cellBlank->isError());
	ASSERT_EQ(false, cellBlank->isBoolean());
	ASSERT_EQ(false, cellBlank->isFloat());
	ASSERT_EQ(false, cellBlank->isSkip());
	ASSERT_EQ(false, cellBlank->isString());
	ASSERT_EQ(false, cellBlank->isInteger());

	ASSERT_EQ("", cellBlank->asString());
	ASSERT_EQ(0, cellBlank->asInteger());
	ASSERT_EQ(false, cellBlank->asBoolean());
	ASSERT_EQ(0.0, cellBlank->asFloat());
}

TEST_F(CellEmptyTest, testSkipType) {
	ASSERT_EQ(1, cellSkip->getRefCount());
	ASSERT_EQ(true, cellSkip->isSkip());

	ASSERT_EQ(false, cellSkip->isError());
	ASSERT_EQ(false, cellSkip->isBoolean());
	ASSERT_EQ(false, cellSkip->isFloat());
	ASSERT_EQ(false, cellSkip->isBlank());
	ASSERT_EQ(false, cellSkip->isString());
	ASSERT_EQ(false, cellSkip->isInteger());

	ASSERT_EQ("", cellSkip->asString());
	ASSERT_EQ(0, cellSkip->asInteger());
	ASSERT_EQ(false, cellSkip->asBoolean());
	ASSERT_EQ(0.0, cellSkip->asFloat());
}

	} // end namespace xltable
} // end namespace aquila
