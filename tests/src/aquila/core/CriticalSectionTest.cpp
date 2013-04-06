/**
 * ============================================================================
 * 2011/07/23
 * $Id: CriticalSectionTest.cpp 96 2011-08-11 17:36:58Z whirlwind $ Juno
 * ============================================================================
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/core/auto_drop.h"
#include "aquila/core/CriticalSection.h"
#include "aquila/core/MockWinApi.h"

using namespace testing;

namespace aquila {
	namespace core {

class CriticalSectionTest : public ::testing::Test {
protected:
	MockWinApi winApi;
};

TEST_F(CriticalSectionTest, testConstructorIncrementsRefCounter) {{
	InSequence s;
	EXPECT_CALL(winApi, InitializeCriticalSection(_)).Times(1);
	EXPECT_CALL(winApi, DeleteCriticalSection(_)).Times(1);
	auto_drop<CriticalSection> cs(new CriticalSection(&winApi));

	ASSERT_EQ(2, winApi.getRefCount());
}}

TEST_F(CriticalSectionTest, testDestructorDecrementsRefCounter) {{
	InSequence s;
	EXPECT_CALL(winApi, InitializeCriticalSection(_)).Times(1);
	EXPECT_CALL(winApi, DeleteCriticalSection(_)).Times(1);

	CriticalSection* cs = new CriticalSection(&winApi);
	delete cs;
	ASSERT_EQ(1, winApi.getRefCount());
}}

TEST_F(CriticalSectionTest, testAccessors) {{
	InSequence s;
	EXPECT_CALL(winApi, InitializeCriticalSection(_)).Times(1);
	EXPECT_CALL(winApi, DeleteCriticalSection(_)).Times(1);
	auto_drop<CriticalSection> cs(new CriticalSection(&winApi));

	ASSERT_EQ(&winApi, cs->getWinApi());
}}

TEST_F(CriticalSectionTest, testEnter) {{
	InSequence s;
	EXPECT_CALL(winApi, InitializeCriticalSection(_)).Times(1);
	EXPECT_CALL(winApi, EnterCriticalSection(_)).Times(1);
	EXPECT_CALL(winApi, DeleteCriticalSection(_)).Times(1);
	auto_drop<CriticalSection> cs(new CriticalSection(&winApi));

	cs->enter();
}}

TEST_F(CriticalSectionTest, testLeave) {{
	InSequence s;
	EXPECT_CALL(winApi, InitializeCriticalSection(_)).Times(1);
	EXPECT_CALL(winApi, LeaveCriticalSection(_)).Times(1);
	EXPECT_CALL(winApi, DeleteCriticalSection(_)).Times(1);
	auto_drop<CriticalSection> cs(new CriticalSection(&winApi));

	cs->leave();
}}

	} // end namespace core
} // end namespace aquila