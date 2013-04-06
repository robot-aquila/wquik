/**
 * ============================================================================
 * 2011/07/24
 * $Id: EventTest.cpp 104 2011-08-15 09:47:48Z whirlwind $ Juno
 * ============================================================================
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/core/auto_drop.h"
#include "aquila/core/MockWinApi.h"
#include "aquila/core/Event.h"

using namespace testing;

namespace aquila {
	namespace core {

class EventTest : public ::testing::Test {
protected:
	MockWinApi winApi;

	void EXPECT_CONSTRUCTOR_CALLS() {
		EXPECT_CALL(winApi, CreateEvent((LPSECURITY_ATTRIBUTES)88876,
				TRUE, FALSE, StrEq(TEXT("foobar"))))
			.Times(1)
			.WillOnce(Return((HANDLE)11122));
	}

	void EXPECT_DESTRUCTOR_CALLS() {
		EXPECT_CALL(winApi, CloseHandle((HANDLE)11122))
			.Times(1)
			.WillOnce(Return(TRUE));
	}

};

TEST_F(EventTest, testConstructorDestructorCalls) {{
	InSequence s;
	EXPECT_CONSTRUCTOR_CALLS();
	EXPECT_DESTRUCTOR_CALLS();

	auto_drop<Event> e(new Event
		(&winApi, (LPSECURITY_ATTRIBUTES)88876, TRUE, FALSE, TEXT("foobar")));

	ASSERT_EQ(2, winApi.getRefCount());
}}

TEST_F(EventTest, testConstructorThrowsIfCreateEventFailed) {{
	InSequence s;
	EXPECT_CALL(winApi, CreateEvent((LPSECURITY_ATTRIBUTES)88876,
			TRUE, FALSE, StrEq(TEXT("foobar"))))
		.Times(1)
		.WillOnce(Return((HANDLE)NULL));
	EXPECT_CALL(winApi, GetLastError())
		.Times(1)
		.WillOnce(Return(5567));

	ASSERT_THROW(auto_drop<Event> e(new Event(&winApi,
		(LPSECURITY_ATTRIBUTES)88876, TRUE, FALSE, TEXT("foobar"))),
		WinApiErrorException);
}}

TEST_F(EventTest, testAccessors) {{
	InSequence s;
	EXPECT_CONSTRUCTOR_CALLS();
	EXPECT_DESTRUCTOR_CALLS();

	auto_drop<Event> e(new Event
		(&winApi, (LPSECURITY_ATTRIBUTES)88876, TRUE, FALSE, TEXT("foobar")));
	ASSERT_EQ((HANDLE)11122, e->getHandle());
	ASSERT_EQ(&winApi, e->getWinApi());
}}

TEST_F(EventTest, testPulse_Ok) {{
	InSequence s;
	EXPECT_CONSTRUCTOR_CALLS();
	EXPECT_CALL(winApi, PulseEvent((HANDLE)11122))
		.Times(1)
		.WillOnce(Return(TRUE));
	EXPECT_DESTRUCTOR_CALLS();

	auto_drop<Event> e(new Event
		(&winApi, (LPSECURITY_ATTRIBUTES)88876, TRUE, FALSE, TEXT("foobar")));
	e->pulse();
}}

TEST_F(EventTest, testPulse_ThrowsOnError) {{
	InSequence s;
	EXPECT_CONSTRUCTOR_CALLS();
	EXPECT_CALL(winApi, PulseEvent((HANDLE)11122))
		.Times(1)
		.WillOnce(Return(FALSE));
	EXPECT_CALL(winApi, GetLastError())
		.Times(1)
		.WillOnce(Return(12345));
	EXPECT_DESTRUCTOR_CALLS();

	auto_drop<Event> e(new Event
		(&winApi, (LPSECURITY_ATTRIBUTES)88876, TRUE, FALSE, TEXT("foobar")));

	ASSERT_THROW(e->pulse(), WinApiErrorException);
}}

TEST_F(EventTest, testSet_Ok) {{
	InSequence s;
	EXPECT_CONSTRUCTOR_CALLS();
	EXPECT_CALL(winApi, SetEvent((HANDLE)11122))
		.Times(1)
		.WillOnce(Return(TRUE));
	EXPECT_DESTRUCTOR_CALLS();

	auto_drop<Event> e(new Event
		(&winApi, (LPSECURITY_ATTRIBUTES)88876, TRUE, FALSE, TEXT("foobar")));
	e->set();
}}

TEST_F(EventTest, testSet_ThrowsOnError) {{
	InSequence s;
	EXPECT_CONSTRUCTOR_CALLS();
	EXPECT_CALL(winApi, SetEvent((HANDLE)11122))
		.Times(1)
		.WillOnce(Return(FALSE));
	EXPECT_CALL(winApi, GetLastError())
		.Times(1)
		.WillOnce(Return(12345));
	EXPECT_DESTRUCTOR_CALLS();

	auto_drop<Event> e(new Event
		(&winApi, (LPSECURITY_ATTRIBUTES)88876, TRUE, FALSE, TEXT("foobar")));

	ASSERT_THROW(e->set(), WinApiErrorException);
}}

TEST_F(EventTest, testReset_Ok) {{
	InSequence s;
	EXPECT_CONSTRUCTOR_CALLS();
	EXPECT_CALL(winApi, ResetEvent((HANDLE)11122))
		.Times(1)
		.WillOnce(Return(TRUE));
	EXPECT_DESTRUCTOR_CALLS();

	auto_drop<Event> e(new Event
		(&winApi, (LPSECURITY_ATTRIBUTES)88876, TRUE, FALSE, TEXT("foobar")));
	e->reset();
}}

TEST_F(EventTest, testReset_ThrowsOnError) {{
	InSequence s;
	EXPECT_CONSTRUCTOR_CALLS();
	EXPECT_CALL(winApi, ResetEvent((HANDLE)11122))
		.Times(1)
		.WillOnce(Return(FALSE));
	EXPECT_CALL(winApi, GetLastError())
		.Times(1)
		.WillOnce(Return(12345));
	EXPECT_DESTRUCTOR_CALLS();

	auto_drop<Event> e(new Event
		(&winApi, (LPSECURITY_ATTRIBUTES)88876, TRUE, FALSE, TEXT("foobar")));

	ASSERT_THROW(e->reset(), WinApiErrorException);
}}

TEST_F(EventTest, testWait_Ok) {{
	InSequence s;
	EXPECT_CONSTRUCTOR_CALLS();
	EXPECT_CALL(winApi, WaitForSingleObject((HANDLE)11122, INFINITE))
		.Times(1)
		.WillOnce(Return(WAIT_OBJECT_0));
	EXPECT_DESTRUCTOR_CALLS();

	auto_drop<Event> e(new Event
		(&winApi, (LPSECURITY_ATTRIBUTES)88876, TRUE, FALSE, TEXT("foobar")));

	e->wait();
}}

TEST_F(EventTest, testWait_ThrowsOnError) {{
	InSequence s;
	EXPECT_CONSTRUCTOR_CALLS();
	EXPECT_CALL(winApi, WaitForSingleObject((HANDLE)11122, INFINITE))
		.Times(1)
		.WillOnce(Return(WAIT_FAILED));
	EXPECT_CALL(winApi, GetLastError())
		.Times(1)
		.WillOnce(Return(12345));
	EXPECT_DESTRUCTOR_CALLS();

	auto_drop<Event> e(new Event
		(&winApi, (LPSECURITY_ATTRIBUTES)88876, TRUE, FALSE, TEXT("foobar")));

	ASSERT_THROW(e->wait(), WinApiErrorException);
}}

	} // end namespace core
} // end namespace aquila