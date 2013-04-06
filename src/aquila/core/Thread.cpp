/**
 * ============================================================================
 * 2011/07/24
 * $Id: Thread.cpp 235 2012-07-23 15:52:48Z whirlwind $ Juno
 * ============================================================================
 */

#include "aquila/core/Thread.h"
#include "aquila/core/Lock.h"

namespace aquila {
	namespace core {

Thread::Thread(IWinApi* pWinApi, ICriticalSection* pCs, IRunnable* pRunnable)
: winApi(pWinApi),
  cs(pCs),
  runnable(pRunnable),
  hThread(NULL),
  dwThreadId(0)
{

}

Thread::~Thread() {
	if ( hThread != NULL ) {
		winApi->CloseHandle(hThread);
	}
}

DWORD Thread::ThreadFunction(LPVOID pParam) {
	return ((Thread*)pParam)->runnable->run();
}

void Thread::start() {
	Lock lock(cs);
	if ( hThread != NULL ) {
		throw std::exception("Thread already started");
	}
	hThread = winApi->CreateThread(NULL, 0, Thread::ThreadFunction,
		(LPVOID)this, 0, &dwThreadId);
	if ( hThread == NULL ) {
		dwThreadId = 0;
		throw WinApiErrorException("CreateThread failed", winApi);
	}
}

bool Thread::isAlive() {
	cs->enter();
	HANDLE handle = hThread;
	cs->leave();

	if ( handle == NULL ) {
		return false;
	}
	DWORD dwStatus;
	if ( winApi->GetExitCodeThread(handle, &dwStatus) ) {
		return dwStatus == STILL_ACTIVE ? true : false;
	}
	throw WinApiErrorException("GetExitCodeThread failed", winApi);
}

void Thread::join() {
	cs->enter();
	HANDLE handle = hThread;
	cs->leave();
	if ( handle == NULL ) {
		throw std::exception("Thread not started");
	}
	winApi->WaitForSingleObject(handle, INFINITE);
}

DWORD Thread::getExitCode() {
	cs->enter();
	HANDLE handle = hThread;
	cs->leave();
	if ( handle == NULL ) {
		throw std::exception("Thread not started");
	}
	DWORD dwStatus;
	if ( winApi->GetExitCodeThread(handle, &dwStatus) ) {
		return dwStatus;
	}
	throw WinApiErrorException("GetExitCodeThread failed", winApi);
}

HANDLE Thread::getHandle() {
	Lock lock(cs);
	return hThread;
}

DWORD Thread::getId() {
	Lock lock(cs);
	return dwThreadId;
}

IWinApi* Thread::getWinApi() {
	return winApi;
}

ICriticalSection* Thread::getCriticalSection() {
	return cs;
}

IRunnable* Thread::getRunnable() {
	return runnable;
}

	} // end namespace core
} // end namespace aquila