/**
 * ============================================================================
 * 2011/07/29
 * $Id: HelperWindowController.cpp 235 2012-07-23 15:52:48Z whirlwind $
 * ============================================================================
 */

#include "aquila/ddesvr/HelperWindowController.h"

namespace aquila {
	namespace ddesvr {

HelperWindowController::HelperWindowController(aquila::core::IWinApi *pWinApi,
											   HWND hWindow)
  : winApi(pWinApi),
	hWnd(hWindow)
{

}

HelperWindowController::~HelperWindowController() {

}

void HelperWindowController::registerService(long serviceId) {
	winApi->SendMessage(hWnd, WM_HELPER_REGISTER, 0, serviceId);
}

void HelperWindowController::unregisterService(long serviceId) {
	winApi->SendMessage(hWnd, WM_HELPER_UNREGISTER, 0, serviceId);
}

void HelperWindowController::close() {
	//winApi->PostMessage(hWnd, WM_HELPER_EXIT, 0, 0);
	winApi->SendMessage(hWnd, WM_HELPER_EXIT, 0, 0);
}

IWinApi* HelperWindowController::getWinApi() {
	return winApi;
}

HWND HelperWindowController::getWindowHandle() {
	return hWnd;
}

	} // end namespace ddesvr
} // end namespace aquil