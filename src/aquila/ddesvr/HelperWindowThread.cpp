/**
 * ============================================================================
 * 2011/08/03
 * $Id: HelperWindowThread.cpp 104 2011-08-15 09:47:48Z whirlwind $
 * ============================================================================
 */

#include "aquila/ddesvr/HelperWindowThread.h"

namespace aquila {
	namespace ddesvr {

HelperWindowThread::HelperWindowThread(IHelperWindow* pWindow,
									   IEvent* pEvent)
									   : e(pEvent),
										 window(pWindow),
										 controller(NULL)
{

}

HelperWindowThread::~HelperWindowThread() {
	if ( controller != NULL ) {
		controller->drop();
		controller = NULL;
	}
}

DWORD HelperWindowThread::run() {
	window->registerClass();
	controller = window->createWindow();
	e->set();
	window->messageLoop();
	window->unregisterClass();
	return 0;
}

IHelperWindowController* HelperWindowThread::getWindowController() {
	return controller;
}

IHelperWindow* HelperWindowThread::getWindow() {
	return window;
}

IEvent* HelperWindowThread::getEvent() {
	return e;
}

	} // end namespace ddesvr
} // end namespace aquila