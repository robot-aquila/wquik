#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/xltable/CellAggregator.h"
#include "aquila/xltable/MockCellFactory.h"
#include "aquila/xltable/CellInteger.h"

using namespace testing;

namespace aquila {
	namespace xltable {

class CellAggregatorTest : public ::testing::Test {
protected:
	MockCellFactory factory;
	CellAggregator* cells;
	ICell* cell1;
	ICell* cell2;

	virtual void SetUp() {
		cells = new CellAggregator(&factory);
		cell1 = new CellInteger(12345); cell1->grab();
		cell2 = new CellInteger(54321); cell2->grab();
	}

	virtual void TearDown() {
		if ( cells != 0 ) {
			cells->drop();
		}
		delete cell1;
		delete cell2;
	}

};

TEST_F(CellAggregatorTest, testConstructor) {
	ASSERT_EQ(1, cells->getRefCount());
	ASSERT_EQ(2, factory.getRefCount());
	ASSERT_EQ(0, cells->getCellCount());
}

TEST_F(CellAggregatorTest, testDestructor) {
	cells->addCell(cell1);
	cells->addCell(cell2);
	ASSERT_EQ(2, cell1->getRefCount()); // счетчик не изменился
	ASSERT_EQ(2, cell2->getRefCount());

	cells->drop(); cells = 0;

	ASSERT_EQ(1, cell1->getRefCount()); // счетчик ссылок уменьшается
	ASSERT_EQ(1, cell2->getRefCount());
	ASSERT_EQ(1, factory.getRefCount()); // у фабрики тоже
}

TEST_F(CellAggregatorTest, testAddGetCell) {
	ASSERT_EQ(0, cells->addCell(cell1));
	ASSERT_EQ(1, cells->getCellCount());
	ASSERT_EQ(2, cell1->getRefCount()); // счетчик ссылок не увеличивает
	ASSERT_EQ(cell1, cells->getCell(0));

	ASSERT_EQ(1, cells->addCell(cell2));
	ASSERT_EQ(2, cells->getCellCount());
	ASSERT_EQ(2, cell2->getRefCount()); // счетчик ссылок не увеличивает
	ASSERT_EQ(cell2, cells->getCell(1));
}

TEST_F(CellAggregatorTest, testGetCellThrowsIfOutOfRange) {
	try {
		cells->getCell(123);
		ADD_FAILURE() << "Expected exception: XltException";
	} catch ( XltException e ) {
		ASSERT_EQ((string)"Cell index out of range", e.what());
		SUCCEED();
	} catch ( ... ) {
		FAIL() << "Uncaught exception";
	}
}

TEST_F(CellAggregatorTest, testAddFloat) {
	try {
		EXPECT_CALL(factory, createFloat(12.34))
			.Times(1)
			.WillOnce(Return(cell1));

		ASSERT_EQ(0, cells->addFloat(12.34));
		ASSERT_EQ(cell1, cells->getCell(0));
	} catch ( ... ) {
		FAIL() << "Uncaught exception";
	}
}

TEST_F(CellAggregatorTest, testAddBoolean) {
	try {
		EXPECT_CALL(factory, createBoolean(true))
			.Times(1)
			.WillOnce(Return(cell1));

		ASSERT_EQ(0, cells->addBoolean(true));
		ASSERT_EQ(cell1, cells->getCell(0));
	} catch ( ... ) {
		FAIL() << "Uncaught exception";
	}
}

TEST_F(CellAggregatorTest, testAddString) {
	try {
		EXPECT_CALL(factory, createString("zulu4", 5))
			.Times(1)
			.WillOnce(Return(cell1));

		ASSERT_EQ(0, cells->addString("zulu4", 5));
		ASSERT_EQ(cell1, cells->getCell(0));
	} catch ( ... ) {
		FAIL() << "Uncaught exception";
	}
}

TEST_F(CellAggregatorTest, testAddInteger) {
	try {
		EXPECT_CALL(factory, createInteger(1234))
			.Times(1)
			.WillOnce(Return(cell1));

		ASSERT_EQ(0, cells->addInteger(1234));
		ASSERT_EQ(cell1, cells->getCell(0));
	} catch ( ... ) {
		FAIL() << "Uncaught exception";
	}
}

TEST_F(CellAggregatorTest, testAddError) {
	try {
		EXPECT_CALL(factory, createError())
			.Times(1)
			.WillOnce(Return(cell1));

		ASSERT_EQ(0, cells->addError());
		ASSERT_EQ(cell1, cells->getCell(0));
	} catch ( ... ) {
		FAIL() << "Uncaught exception";
	}
}

TEST_F(CellAggregatorTest, testAddBlank) {
	try {
		EXPECT_CALL(factory, createBlank())
			.Times(1)
			.WillOnce(Return(cell1));

		ASSERT_EQ(0, cells->addBlank());
		ASSERT_EQ(cell1, cells->getCell(0));
	} catch ( ... ) {
		FAIL() << "Uncaught exception";
	}
}

TEST_F(CellAggregatorTest, testAddSkip) {
	try {
		EXPECT_CALL(factory, createSkip())
			.Times(1)
			.WillOnce(Return(cell1));

		ASSERT_EQ(0, cells->addSkip());
		ASSERT_EQ(cell1, cells->getCell(0));
	} catch ( ... ) {
		FAIL() << "Uncaught exception";
	}
}


	} // end namespace xltable
} // end namespace aquila
