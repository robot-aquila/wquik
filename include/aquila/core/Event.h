/**
 * ============================================================================
 * 2011/07/24
 * $Id: Event.h 104 2011-08-15 09:47:48Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#pragma warning(disable:4290)
#include "aquila/core/IEvent.h"
#include "aquila/core/auto_grab.h"

namespace aquila {
	namespace core {

class Event : public IEvent {
public:
	Event(IWinApi* pWinApi, LPSECURITY_ATTRIBUTES pEventAttributes,
		BOOL bManualReset, BOOL bInitialState, LPCTSTR pName);

	virtual ~Event();

	virtual HANDLE getHandle();

	virtual void pulse() throw (WinApiErrorException);

	virtual void set() throw (WinApiErrorException);

	virtual void reset() throw (WinApiErrorException);

	virtual void wait() throw (WinApiErrorException);

	IWinApi* getWinApi();

private:
	auto_grab<IWinApi> winApi;
	HANDLE hEvent;

};

	} // end namespace core
} // end namespace aquila