/**
 * ============================================================================
 * 2011/07/29
 * $Id: Mutex.h 104 2011-08-15 09:47:48Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#include "aquila/core/IMutex.h"

namespace aquila {
	namespace core {

class Mutex : public IMutex {
public:

	Mutex(const char* name) {
		hMutex = ::CreateMutex(NULL, FALSE, name);
		if ( hMutex == NULL ) {
			throw WinApiErrorException("CreateMutex failed", ::GetLastError());
		}
		if ( ::WaitForSingleObject(hMutex, INFINITE) == WAIT_FAILED ) {
			::CloseHandle(hMutex);
			throw WinApiErrorException("WaitForSingleObject failed",
				::GetLastError());
		}
	}

	virtual ~Mutex() {
		::ReleaseMutex(hMutex);
		::CloseHandle(hMutex);
	}

	virtual HANDLE getHandle() {
		return hMutex;
	}

private:
	HANDLE hMutex;
};

	} // end namespace core
} // end namespace aquila