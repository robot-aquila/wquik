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
 * Объектная реализация потока.
 */
class Thread : public IThread {
public:

	Thread(IWinApi* pWinApi, ICriticalSection* pCs, IRunnable* pRunnable);

	/**
	 * Деструктор закрывает дескриптор потока, если он открыт. При этом,
	 * поведение при вызове деструктора из связанного потока неопределено.
	 * В связи с этим, не рекомендуется передавать объект потока в
	 * связанный поток.
	 */
	virtual ~Thread();

	/** 
	 * Запустить поток.
	 */
	virtual void start() throw(std::exception, WinApiErrorException);

	/**
	 * Проверка факта исполнения потока.
	 */
	virtual bool isAlive();

	/**
	 * Ожидать завершения потока.
	 *
	 * Выбрасывает исключение, если поток не был запущен.
	 */
	virtual void join() throw(std::exception, WinApiErrorException);

	/**
	 * Получить код завершения потока.
	 */
	virtual DWORD getExitCode() throw(std::exception, WinApiErrorException);

	/**
	 * Получить дескриптор потока.
	 */
	virtual HANDLE getHandle();

	/**
	 * Получить идентификатор потока.
	 */
	virtual DWORD getId();

	/**
	 * Получить экземпляр объектной оболочки функций WinApi.
	 */
	IWinApi* getWinApi();

	/**
	 * Получить экземпляр критической секции.
	 */
	ICriticalSection* getCriticalSection();

	/**
	 * Получить экземпляр функции потока.
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