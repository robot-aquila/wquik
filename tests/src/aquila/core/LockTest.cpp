/**
 * ============================================================================
 * 2011/07/23
 * $Id: LockTest.cpp 96 2011-08-11 17:36:58Z whirlwind $ Juno
 * ============================================================================
 */
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/core/auto_drop.h"
#include "aquila/core/Lock.h"
#include "aquila/core/MockCriticalSection.h"

using namespace testing;

namespace aquila {
	namespace core {

class LockTest : public ::testing::Test {
protected:
	MockCriticalSection cs;
};

TEST_F(LockTest, testEnterLeave) {{
	InSequence s;
	EXPECT_CALL(cs, enter()).Times(1);
	EXPECT_CALL(cs, leave()).Times(1);

	auto_drop<Lock> lock(new Lock(&cs));
}}

TEST_F(LockTest, testAccessors) {{
	InSequence s;
	EXPECT_CALL(cs, enter()).Times(1);
	EXPECT_CALL(cs, leave()).Times(1);

	auto_drop<Lock> lock(new Lock(&cs));
	ASSERT_EQ(&cs, lock->getCriticalSection());
}}

	} // end namespace core
} // end namespace aquila
