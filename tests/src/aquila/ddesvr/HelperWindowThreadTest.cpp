/**
 * ============================================================================
 * 2011/08/03
 * $Id: HelperWindowThreadTest.cpp 104 2011-08-15 09:47:48Z whirlwind $ Juno
 * ============================================================================
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/core/auto_drop.h"
#include "aquila/ddesvr/MockHelperWindow.h"
#include "aquila/ddesvr/MockHelperWindowController.h"
#include "aquila/ddesvr/HelperWindowThread.h"
#include "aquila/core/MockEvent.h"

using namespace testing;
using namespace aquila::core;

namespace aquila {
	namespace ddesvr {

class HelperWindowThreadTest : public ::testing::Test {
protected:
	MockEvent e;
	MockHelperWindow window;
	MockHelperWindowController controller;
};

TEST_F(HelperWindowThreadTest, testConstructorIncrementsRefCount) {{
	auto_drop<HelperWindowThread> t(new HelperWindowThread(&window, &e));
	ASSERT_EQ(2, window.getRefCount());
	ASSERT_EQ(2, e.getRefCount());
}}

TEST_F(HelperWindowThreadTest, testDestructorDecrementsRefCount) {{
	HelperWindowThread* t = new HelperWindowThread(&window, &e);
	delete t;
	ASSERT_EQ(1, window.getRefCount());
	ASSERT_EQ(1, e.getRefCount());
}}

TEST_F(HelperWindowThreadTest, testAccessors) {{
	auto_drop<HelperWindowThread> t(new HelperWindowThread(&window, &e));
	ASSERT_EQ(&window, t->getWindow());
	ASSERT_EQ(&e, t->getEvent());
	ASSERT_EQ(NULL, t->getWindowController());
}}

TEST_F(HelperWindowThreadTest, testRun) {{
	InSequence s;
	EXPECT_CALL(window, registerClass()).Times(1);
	EXPECT_CALL(window, createWindow())
		.Times(1)
		.WillOnce(Return(&controller));
	EXPECT_CALL(e, set())
		.Times(1);
	EXPECT_CALL(window, messageLoop())
		.Times(1);
	EXPECT_CALL(window, unregisterClass())
		.Times(1);

	auto_drop<HelperWindowThread> t(new HelperWindowThread(&window, &e));
	ASSERT_EQ(0, t->run());

	ASSERT_EQ(&controller, t->getWindowController());
	t->setWindowController(NULL); // что бы не дропал
}}

TEST_F(HelperWindowThreadTest, testDestructorFreesController) {{
	controller.grab();

	HelperWindowThread* t = new HelperWindowThread(&window, &e);
	t->setWindowController(&controller);
	delete t;

	ASSERT_EQ(1, controller.getRefCount());
}}

	} // end namespace ddesvr
} // end namespace aquila