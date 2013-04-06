/**
 * ============================================================================
 * 2011/07/24
 * $Id: ThreadTest.cpp 235 2012-07-23 15:52:48Z whirlwind $ Juno
 * ============================================================================
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/core/auto_drop.h"
#include "aquila/core/MockWinApi.h"
#include "aquila/core/MockRunnable.h"
#include "aquila/core/MockCriticalSection.h"
#include "aquila/core/Thread.h"

using namespace testing;

namespace aquila {
	namespace core {

class ThreadTest : public ::testing::Test {
protected:
	MockWinApi winApi;
	MockCriticalSection cs;
	MockRunnable runnable;

	/**
	 * Установить ожидание последовательности вызовов запуска потока.
	 */
	void EXPECT_START_CALLS(IThread* pThread) {
		EXPECT_CALL(cs, enter()).Times(1);
		EXPECT_CALL(winApi,
				CreateThread(NULL, 0, Thread::ThreadFunction, pThread, 0, _))
			.Times(1)
			.WillOnce(DoAll(
					SetArgumentPointee<5>(556677), // Устанавливает id потока
					Return((HANDLE)889922) // возвращает дескриптор потока
			));
		EXPECT_CALL(cs, leave()).Times(1);
	}

	/**
	 * Установить ожидание закрытие дескриптора
	 */
	void EXPECT_CLOSE_HANDLE_CALL() {
		EXPECT_CALL(winApi, CloseHandle((HANDLE)889922)).Times(1);
	}

};

TEST_F(ThreadTest, testConstructorIncrementsRefCounter) {{
	auto_drop<Thread> thread(new Thread(&winApi, &cs, &runnable));

	ASSERT_EQ(2, winApi.getRefCount());
	ASSERT_EQ(2, cs.getRefCount());
	ASSERT_EQ(2, runnable.getRefCount());
}}

TEST_F(ThreadTest, testDestructorDecrementsRefCounter) {{
	Thread* thread = new Thread(&winApi, &cs, &runnable);
	delete thread;

	ASSERT_EQ(1, winApi.getRefCount());
	ASSERT_EQ(1, cs.getRefCount());
	ASSERT_EQ(1, runnable.getRefCount());
}}

TEST_F(ThreadTest, testAccessorsImmutables_AfterConstruct) {{
	auto_drop<Thread> thread(new Thread(&winApi, &cs, &runnable));

	ASSERT_EQ(&winApi, thread->getWinApi());
	ASSERT_EQ(&cs, thread->getCriticalSection());
	ASSERT_EQ(&runnable, thread->getRunnable());
}}

TEST_F(ThreadTest, testGetHandle_IfNotStarted) {{
	auto_drop<Thread> thread(new Thread(&winApi, &cs, &runnable));

	EXPECT_CALL(cs, enter()).Times(1);
	EXPECT_CALL(cs, leave()).Times(1);
	ASSERT_EQ(NULL, thread->getHandle());
}}

TEST_F(ThreadTest, testGetHandle_IfStarted) {{
	auto_drop<Thread> thread(new Thread(&winApi, &cs, &runnable));

	thread->test_setThreadValues((HANDLE)11223, NULL);
	EXPECT_CALL(cs, enter()).Times(1);
	EXPECT_CALL(cs, leave()).Times(1);
	ASSERT_EQ((HANDLE)11223, thread->getHandle());
	thread->test_resetThreadValues();
}}

TEST_F(ThreadTest, testGetId_IfNotStarted) {{
	auto_drop<Thread> thread(new Thread(&winApi, &cs, &runnable));

	EXPECT_CALL(cs, enter()).Times(1);
	EXPECT_CALL(cs, leave()).Times(1);
	ASSERT_EQ(0, thread->getId());
}}

TEST_F(ThreadTest, testGetId_IfStarted) {{
	auto_drop<Thread> thread(new Thread(&winApi, &cs, &runnable));

	thread->test_setThreadValues(NULL, 56789);
	EXPECT_CALL(cs, enter()).Times(1);
	EXPECT_CALL(cs, leave()).Times(1);
	ASSERT_EQ(56789, thread->getId());
	thread->test_resetThreadValues();
}}

TEST_F(ThreadTest, testStart_Ok) {{
	InSequence s;
	auto_drop<Thread> thread(new Thread(&winApi, &cs, &runnable));

	EXPECT_START_CALLS(thread);
	EXPECT_CLOSE_HANDLE_CALL();

	thread->start();
	ASSERT_EQ((HANDLE)889922, thread->test_getThreadHandle());
	ASSERT_EQ(556677, thread->test_getThreadId());
}}

TEST_F(ThreadTest, testStart_ThrowsIfAlreadyStarted) {{
	InSequence s;
	auto_drop<Thread> thread(new Thread(&winApi, &cs, &runnable));

	EXPECT_START_CALLS(thread);
	EXPECT_CALL(cs, enter()).Times(1);
	EXPECT_CALL(cs, leave()).Times(1);
	EXPECT_CLOSE_HANDLE_CALL();

	thread->start();
	ASSERT_THROW(thread->start(), std::exception);
}}

TEST_F(ThreadTest, testStart_ThrowsIfCreateThreadFailed) {{
	InSequence s;
	auto_drop<Thread> thread(new Thread(&winApi, &cs, &runnable));

	EXPECT_CALL(cs, enter()).Times(1);
	EXPECT_CALL(winApi, CreateThread(NULL, 0, Thread::ThreadFunction,
			(LPVOID)thread.get(), 0, _))
		.Times(1)
		.WillOnce(Return((HANDLE)NULL));
	EXPECT_CALL(winApi, GetLastError())
		.Times(1)
		.WillOnce(Return(12345)); // called by WinApiErrotException
	EXPECT_CALL(cs, leave()).Times(1);

	ASSERT_THROW(thread->start(), WinApiErrorException);
	ASSERT_EQ(NULL, thread->test_getThreadHandle());
	ASSERT_EQ(0, thread->test_getThreadId());
}}

TEST_F(ThreadTest, testIsAlive_ReturnsFalseIfThreadNotStarted) {{
	InSequence s;
	auto_drop<Thread> thread(new Thread(&winApi, &cs, &runnable));

	EXPECT_CALL(cs, enter()).Times(1);
	EXPECT_CALL(cs, leave()).Times(1);

	ASSERT_FALSE(thread->isAlive());
}}


TEST_F(ThreadTest, testIsAlive_ReturnsFalseIfThreadFinished) {{
	InSequence s;
	auto_drop<Thread> thread(new Thread(&winApi, &cs, &runnable));

	thread->test_setThreadValues((HANDLE)889922, 556677);
	EXPECT_CALL(cs, enter()).Times(1);
	// критическая секция используется для копирования дескриптора потока
	EXPECT_CALL(cs, leave()).Times(1);
	EXPECT_CALL(winApi, GetExitCodeThread((HANDLE)889922, _))
		.Times(1)
		.WillOnce(DoAll(
			SetArgumentPointee<1>(1234),
			Return(TRUE)
		));

	ASSERT_FALSE(thread->isAlive());
	thread->test_resetThreadValues();
}}

TEST_F(ThreadTest, testIsAlive_ThrowsIfGetExitCodeThreadFails) {{
	InSequence s;
	auto_drop<Thread> thread(new Thread(&winApi, &cs, &runnable));

	thread->test_setThreadValues((HANDLE)889922, 556677);
	EXPECT_CALL(cs, enter()).Times(1);
	EXPECT_CALL(cs, leave()).Times(1);
	EXPECT_CALL(winApi, GetExitCodeThread((HANDLE)889922, _))
		.Times(1)
		.WillOnce(Return(FALSE));
	EXPECT_CALL(winApi, GetLastError())
		.Times(1)
		.WillOnce(Return(12345)); // called by WinApiErrotException

	ASSERT_THROW(thread->isAlive(), WinApiErrorException);
	thread->test_resetThreadValues();
}}

TEST_F(ThreadTest, testIsAlive_ReturnsTrueIfStillActive) {{
	InSequence s;
	auto_drop<Thread> thread(new Thread(&winApi, &cs, &runnable));

	thread->test_setThreadValues((HANDLE)889922, 556677);
	EXPECT_CALL(cs, enter()).Times(1);
	EXPECT_CALL(cs, leave()).Times(1);
	EXPECT_CALL(winApi, GetExitCodeThread((HANDLE)889922, _))
			.Times(1)
			.WillOnce(DoAll(
				SetArgumentPointee<1>(STILL_ACTIVE),
				Return(TRUE)
			));

	ASSERT_TRUE(thread->isAlive());
	thread->test_resetThreadValues();
}}

TEST_F(ThreadTest, testJoin_ThrowsIfNotStarted) {{
	InSequence s;
	auto_drop<Thread> thread(new Thread(&winApi, &cs, &runnable));

	EXPECT_CALL(cs, enter()).Times(1);
	EXPECT_CALL(cs, leave()).Times(1);

	ASSERT_THROW(thread->join(), std::exception);
}}

TEST_F(ThreadTest, testJoin_Ok) {{
	InSequence s;
	auto_drop<Thread> thread(new Thread(&winApi, &cs, &runnable));

	thread->test_setThreadValues((HANDLE)889922, 556677);
	EXPECT_CALL(cs, enter()).Times(1);
	// критическая секция используется только для копирования дескриптора
	EXPECT_CALL(cs, leave()).Times(1);
	EXPECT_CALL(winApi, WaitForSingleObject((HANDLE)889922, INFINITE))
		.Times(1)
		.WillOnce(Return(WAIT_OBJECT_0));

	thread->join();
	thread->test_resetThreadValues();
}}

TEST_F(ThreadTest, testGetExitCode_ThrowsIfNotStarted) {{
	InSequence s;
	auto_drop<Thread> thread(new Thread(&winApi, &cs, &runnable));

	EXPECT_CALL(cs, enter()).Times(1);
	EXPECT_CALL(cs, leave()).Times(1);

	ASSERT_THROW(thread->getExitCode(), std::exception);
}}

TEST_F(ThreadTest, testGetExitCode_ThrowsOnError) {{
	InSequence s;
	auto_drop<Thread> thread(new Thread(&winApi, &cs, &runnable));

	thread->test_setThreadValues((HANDLE)889922, 556677);
	EXPECT_CALL(cs, enter()).Times(1);
	// критическая секция используется только для копирования дескриптора
	EXPECT_CALL(cs, leave()).Times(1);
	EXPECT_CALL(winApi, GetExitCodeThread((HANDLE)889922, _))
			.Times(1)
			.WillOnce(Return(FALSE));
	EXPECT_CALL(winApi, GetLastError())
		.Times(1)
		.WillOnce(Return(12345)); // called by WinApiErrotException

	ASSERT_THROW(thread->getExitCode(), WinApiErrorException);
	thread->test_resetThreadValues();
}}

TEST_F(ThreadTest, testGetExitCode_Ok) {{
	InSequence s;
	auto_drop<Thread> thread(new Thread(&winApi, &cs, &runnable));

	thread->test_setThreadValues((HANDLE)889922, 556677);
	EXPECT_CALL(cs, enter()).Times(1);
	EXPECT_CALL(cs, leave()).Times(1);
	EXPECT_CALL(winApi, GetExitCodeThread((HANDLE)889922, _))
			.Times(1)
			.WillOnce(DoAll(
				SetArgumentPointee<1>(STILL_ACTIVE),
				Return(TRUE)
			));

	ASSERT_EQ(STILL_ACTIVE, thread->getExitCode());
	thread->test_resetThreadValues();
}}

TEST_F(ThreadTest, testThreadFunction) {{
	InSequence s;
	auto_drop<Thread> thread(new Thread(&winApi, &cs, &runnable));

	EXPECT_CALL(runnable, run())
		.Times(1)
		.WillOnce(Return(100500));

	ASSERT_EQ(100500, Thread::ThreadFunction((LPVOID)thread.get()));
}}

	} // end namespace core
} // end namespace aquila