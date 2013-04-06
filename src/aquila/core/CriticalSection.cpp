/**
 * ============================================================================
 * 2011/07/23
 * $Id: CriticalSection.cpp 96 2011-08-11 17:36:58Z whirlwind $ Juno
 * ============================================================================
 */

#include "aquila/core/CriticalSection.h"

namespace aquila {
	namespace core {

CriticalSection::CriticalSection(IWinApi* pWinApi)
	: winApi(pWinApi)
{
	winApi->InitializeCriticalSection(&cs);
}

CriticalSection::~CriticalSection() {
	winApi->DeleteCriticalSection(&cs);
}

IWinApi* CriticalSection::getWinApi() {
	return winApi;
}

void CriticalSection::enter() {
	winApi->EnterCriticalSection(&cs);
}

void CriticalSection::leave() {
	winApi->LeaveCriticalSection(&cs);
}

	} // end namespace core
} // end namespace aquila