#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/xltable/TableRange.h"
#include "aquila/xltable/MockCellAggregator.h"
#include "aquila/xltable/CellInteger.h"

using namespace testing;

namespace aquila {
	namespace xltable {

class TableRangeTest : public ::testing::Test {
protected:
	MockCellAggregator cells;
	ITableRange* table;
	ICell* cell;
	char* topic;
	char* item;

	virtual void SetUp() {
		topic = "topic";
		item = "item";
		table = new TableRange(2, 3, topic, item, &cells);
		cell = new CellInteger(333);
	}

	virtual void TearDown() {
		cell->drop();
		table->drop();
	}

};

TEST_F(TableRangeTest, testConstructor) {
	ASSERT_EQ(1, table->getRefCount());
	ASSERT_EQ(2, cells.getRefCount());
}

TEST_F(TableRangeTest, testGetTopic) {
	ASSERT_EQ((string)table->getTopic(), "topic");
	ASSERT_NE((const char*)table->getTopic(), topic);
}

TEST_F(TableRangeTest, testGetItem) {
	ASSERT_EQ((string)table->getItem(), "item");
	ASSERT_NE((const char*)table->getItem(), item);
}

TEST_F(TableRangeTest, testGetRows) {
	ASSERT_EQ(2, table->getRows());
}

TEST_F(TableRangeTest, testGetCols) {
	ASSERT_EQ(3, table->getCols());
}

TEST_F(TableRangeTest, testGetCell_Ok) {
	EXPECT_CALL(cells, getCell(5)) // row * cols + col
		.Times(1)
		.WillOnce(Return(cell));

	ASSERT_EQ((ICell*)cell, table->getCell(1, 2));
}

TEST_F(TableRangeTest, testGetCell_ThrowsIfRowOutOfRange) {
	try {
		table->getCell(2, 0); // max row=1
		ADD_FAILURE() << "Expected exception: XltException";
	} catch ( XltException & e ) {
		ASSERT_EQ((string)"Row index out of range", e.what());
		SUCCEED();
	} catch ( ... ) {
		FAIL() << "Uncaught exception";
	}
}

TEST_F(TableRangeTest, testGetCell_ThrowsIfColOutOfRange) {
	try {
		table->getCell(0, 3); // max col=2
		ADD_FAILURE() << "Expected exception: XltException";
	} catch ( XltException & e ) {
		ASSERT_EQ((string)"Col index out of range", e.what());
		SUCCEED();
	} catch ( ... ) {
		FAIL() << "Uncaught exception";
	}
}

	} // end namespace xltable
} // end namespace aquila
