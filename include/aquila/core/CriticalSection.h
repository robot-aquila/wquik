/**
 * ============================================================================
 * 2011/07/23
 * $Id: CriticalSection.h 96 2011-08-11 17:36:58Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#include "aquila/core/auto_grab.h"
#include "aquila/core/ICriticalSection.h"
#include "aquila/core/IWinApi.h"

using namespace aquila;

namespace aquila {
	namespace core {

class CriticalSection : public ICriticalSection {
public:
	CriticalSection(IWinApi* winApi);
	~CriticalSection();
	void enter();
	void leave();
	IWinApi* getWinApi();
private:
	CRITICAL_SECTION cs;
	auto_grab<IWinApi> winApi;

};

	} // end namespace core
} // end namespace aquila