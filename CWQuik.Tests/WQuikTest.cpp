#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "wquik/WQuik.h"
#include "wquik/TransactionDriver.h"
#include "wquik/Trans2QuikAPI.h"
#include "wquik/QuikCallbackAPI.h"

using namespace testing;
using namespace wquik;

#ifndef CWQUIK_TESTING
#pragma message ("CWQUIK_TESTING was not defined. Some tests will FAILS!")
#endif

class WQuikTest : public ::testing::Test {
protected:

	virtual void SetUp() {
	}

	virtual void TearDown() {
	}
};

TEST_F(WQuikTest, testCreateStandardDriver) {
	TransactionDriver* driver;
	try {
		driver = (TransactionDriver*)WQuik::createDriver();
		SUCCEED();
	} catch ( WQuikException e ) {
		FAIL() << "Unexpected WQuikException: " << e.what() << "\n";
	}
	ASSERT_NE((TransactionDriver*)0, driver);
#ifndef CWQUIK_TESTING
	FAIL() << "Could not test reference usage without additional methods!\n";
#else
	ASSERT_EQ(1, driver->getRefCount());
	Trans2QuikAPI* apiQuik = (Trans2QuikAPI*)driver->getTrans2QuikAPI();
	ASSERT_EQ(1, apiQuik->getRefCount());
	ASSERT_EQ(1, apiQuik->getLibrary()->getRefCount());
	QuikCallbackAPI* apiCb = (QuikCallbackAPI*)driver->getQuikCallbackAPI();
	ASSERT_EQ(1, apiCb->getRefCount());
	ASSERT_EQ(1, apiCb->getLibrary()->getRefCount());
#endif
}

