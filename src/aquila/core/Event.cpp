/**
 * ============================================================================
 * 2011/07/24
 * $Id: Event.cpp 104 2011-08-15 09:47:48Z whirlwind $ Juno
 * ============================================================================
 */

#include "aquila/core/Event.h"

namespace aquila {
	namespace core {

Event::Event(IWinApi* pWinApi, LPSECURITY_ATTRIBUTES pEventAttributes,
			 BOOL bManualReset, BOOL bInitialState, LPCTSTR pName)
  : winApi(pWinApi),
    hEvent(0)
{
	hEvent = winApi->CreateEvent(pEventAttributes, bManualReset,
		bInitialState, pName);
	if ( hEvent == NULL ) {
		throw WinApiErrorException("CreateEvent failed", winApi);
	}
}

Event::~Event() {
	winApi->CloseHandle(hEvent);
}

HANDLE Event::getHandle() {
	return hEvent;
}

void Event::pulse() {
	if ( ! winApi->PulseEvent(hEvent) ) {
		throw WinApiErrorException("PulseEvent failed", winApi);
	}
}

void Event::set() {
	if ( ! winApi->SetEvent(hEvent) ) {
		throw WinApiErrorException("SetEvent failed", winApi);
	}
}

void Event::reset() {
	if ( ! winApi->ResetEvent(hEvent) ) {
		throw WinApiErrorException("ResetEvent failed", winApi);
	}
}

void Event::wait() {
	if ( winApi->WaitForSingleObject(hEvent, INFINITE) != WAIT_OBJECT_0 ) {
		throw WinApiErrorException("WaitForSingleObject failed", winApi);
	}
}

IWinApi* Event::getWinApi() {
	return winApi;
}

	} // end namespace core
} // end namespace aquila