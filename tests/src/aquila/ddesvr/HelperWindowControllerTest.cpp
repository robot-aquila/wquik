/**
 * ============================================================================
 * 2011/07/29
 * $Id: HelperWindowControllerTest.cpp 101 2011-08-11 18:37:57Z whirlwind $ Juno
 * ============================================================================
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/core/auto_drop.h"
#include "aquila/core/MockWinApi.h"
#include "aquila/ddesvr/HelperWindowController.h"

using namespace testing;

namespace aquila {
	namespace ddesvr {

class HelperWindowControllerTest : public ::testing::Test {
protected:
	MockWinApi winApi;
};

TEST_F(HelperWindowControllerTest, testConstructorIncrementsRefCount) {{
	auto_drop<HelperWindowController>
		c(new HelperWindowController(&winApi, (HWND)765));

	ASSERT_EQ(2, winApi.getRefCount());
}}

TEST_F(HelperWindowControllerTest, testDestructorDecrementsRefCount) {{
	HelperWindowController* c = new HelperWindowController(&winApi, (HWND)567);
	c->drop();

	ASSERT_EQ(1, winApi.getRefCount());
}}

TEST_F(HelperWindowControllerTest, testAccessors) {{
	auto_drop<HelperWindowController>
		c(new HelperWindowController(&winApi, (HWND)765));

	ASSERT_EQ(&winApi, c->getWinApi());
	ASSERT_EQ((HWND)765, c->getWindowHandle());
}}

TEST_F(HelperWindowControllerTest, testRegisterService) {{
	auto_drop<HelperWindowController>
		c(new HelperWindowController(&winApi, (HWND)765));

	EXPECT_CALL(winApi, SendMessage((HWND)765, WM_HELPER_REGISTER, 0, 12345))
		.Times(1)
		.WillOnce(Return((LRESULT)0));

	c->registerService(12345);
}}

TEST_F(HelperWindowControllerTest, testUnregisterService) {{
	auto_drop<HelperWindowController>
		c(new HelperWindowController(&winApi, (HWND)345));

	EXPECT_CALL(winApi, SendMessage((HWND)345, WM_HELPER_UNREGISTER, 0, 5432))
		.Times(1)
		.WillOnce(Return((LRESULT)0));

	c->unregisterService(5432);
}}

TEST_F(HelperWindowControllerTest, testClose) {{
	auto_drop<HelperWindowController>
		c(new HelperWindowController(&winApi, (HWND)246));

	EXPECT_CALL(winApi, SendMessage((HWND)246, WM_HELPER_EXIT, 0, 0))
		.Times(1)
		.WillOnce(Return((LRESULT)0));

	c->close();
}}

	} // end namespace ddesvr
} // end namespace aquila