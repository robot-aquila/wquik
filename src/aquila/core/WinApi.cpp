/**
 * ============================================================================
 * 2011/07/29
 * $Id: WinApi.cpp 96 2011-08-11 17:36:58Z whirlwind $
 * ============================================================================
 */

#include "aquila/core/WinApi.h"

namespace aquila {
	namespace core {

static IWinApi* pInstance = NULL;

IWinApi* WinApi::getInstance() {
	Mutex m(WINAPI_WRAPPER_MUTEX);
	if ( pInstance != NULL ) {
		return (IWinApi*)pInstance->grab();
	}
	pInstance = new WinApi();
	return pInstance;
}

void WinApi::setInstance(IWinApi* pWinApi)  {
	Mutex m(WINAPI_WRAPPER_MUTEX);
	pInstance = pWinApi;
}

WinApi::~WinApi() {
	Mutex m(WINAPI_WRAPPER_MUTEX);
	if ( pInstance == this ) {
		pInstance = NULL;
	}
}

	} // end namespace core
} // end namespace aquila