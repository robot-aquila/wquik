/**
 * ============================================================================
 * 2011/08/03
 * $Id: HelperWindowThread.h 235 2012-07-23 15:52:48Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#include "aquila/core/auto_grab.h"
#include "aquila/core/IEvent.h"
#include "aquila/ddesvr/IHelperWindow.h"
#include "aquila/ddesvr/IHelperWindowThread.h"

namespace aquila {
	namespace ddesvr {

/**
 * ���������� ������� ������ ���������������� ����. � ������ ������� �������
 * ����, �������� ����������� ���������������� ������, ������� ���������� ���� �
 * ������������� �� ���� � ������� ���������� IEvent. ����� �����, ������
 * � ���� ��������� ������� ���������. ����� ���������� ����� ��������� �������,
 * ����������� ������� �������. ���������� �� �������� ����������������.
 */
class HelperWindowThread : public IHelperWindowThread {
public:

	/**
	 * �����������.
	 * pWindow - ������ ����.
	 * pEvent - �������, �������������� ��� ���������������� � ���������� �����
	 *		������������� ����.
	 */
	HelperWindowThread(IHelperWindow* pWindow, IEvent* pEvent);

	virtual ~HelperWindowThread();

	/**
	 * @see IHelperWindowThread::run
	 */
	DWORD run();

	/**
	 * @see IHelperWindowThread::getWindowController
	 */
	IHelperWindowController* getWindowController();

	/**
	 * �������� ��������� ����.
	 */
	IHelperWindow* getWindow();

	IEvent* getEvent();

#ifdef TEST_RUN
	void setWindowController(IHelperWindowController* pController) {
		controller = pController;
	}
#else
#pragma message("Set TEST_RUN definition to enable additional method(s):")
#pragma message("aquila::ddesvr::HelperWindowThread::setWindowController")
#endif


private:
	auto_grab<IEvent> e;
	auto_grab<IHelperWindow> window;
	IHelperWindowController* controller;
};

	} // end namespace ddesvr
} // end namespace aquila