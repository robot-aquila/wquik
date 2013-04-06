/**
 * ============================================================================
 * 2011/07/23
 * $Id: Thread.h 235 2012-07-23 15:52:48Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#include "aquila/core/IThread.h"
#include "aquila/core/IRunnable.h"
#include "aquila/core/ICriticalSection.h"
#include "aquila/core/IWinApi.h"
#include "aquila/core/auto_grab.h"

namespace aquila {
	namespace core {

/**
 * ��������� ���������� ������.
 */
class Thread : public IThread {
public:

	Thread(IWinApi* pWinApi, ICriticalSection* pCs, IRunnable* pRunnable);

	/**
	 * ���������� ��������� ���������� ������, ���� �� ������. ��� ����,
	 * ��������� ��� ������ ����������� �� ���������� ������ ������������.
	 * � ����� � ����, �� ������������� ���������� ������ ������ �
	 * ��������� �����.
	 */
	virtual ~Thread();

	/** 
	 * ��������� �����.
	 */
	virtual void start() throw(std::exception, WinApiErrorException);

	/**
	 * �������� ����� ���������� ������.
	 */
	virtual bool isAlive();

	/**
	 * ������� ���������� ������.
	 *
	 * ����������� ����������, ���� ����� �� ��� �������.
	 */
	virtual void join() throw(std::exception, WinApiErrorException);

	/**
	 * �������� ��� ���������� ������.
	 */
	virtual DWORD getExitCode() throw(std::exception, WinApiErrorException);

	/**
	 * �������� ���������� ������.
	 */
	virtual HANDLE getHandle();

	/**
	 * �������� ������������� ������.
	 */
	virtual DWORD getId();

	/**
	 * �������� ��������� ��������� �������� ������� WinApi.
	 */
	IWinApi* getWinApi();

	/**
	 * �������� ��������� ����������� ������.
	 */
	ICriticalSection* getCriticalSection();

	/**
	 * �������� ��������� ������� ������.
	 */
	IRunnable* getRunnable();

	static DWORD WINAPI ThreadFunction(LPVOID pParam);

#ifdef TEST_RUN

	void test_setThreadValues(HANDLE testHandle, DWORD testId) {
		hThread = testHandle;
		dwThreadId = testId;
	};

	void test_resetThreadValues() {
		test_setThreadValues(NULL, 0);
	}

	HANDLE test_getThreadHandle() {
		return hThread;
	}

	DWORD test_getThreadId() {
		return dwThreadId;
	}

#else
#pragma message("Set TEST_RUN definition to enable additional method(s):")
#pragma message("aquila::core::Thread::test_setThreadValues")
#pragma message("aquila::core::Thread::test_resetThreadValues")
#pragma message("aquila::core::Thread::test_getThreadHandle")
#pragma message("aquila::core::Thread::test_getThreadId")
#endif

private:
	DWORD dwThreadId;
	HANDLE hThread;
	auto_grab<IWinApi> winApi;
	auto_grab<ICriticalSection> cs;
	auto_grab<IRunnable> runnable;

};

	} // end namespace core
} // end namespace aquila