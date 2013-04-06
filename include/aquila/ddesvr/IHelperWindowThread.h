/**
 * ============================================================================
 * 2011/08/03
 * $Id: IHelperWindowThread.h 104 2011-08-15 09:47:48Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#include "aquila/core/IRunnable.h"
#include "aquila/ddesvr/IHelperWindowController.h"
#include "aquila/ddesvr/IHelperWindow.h"

using namespace aquila::core;

namespace aquila {
	namespace ddesvr {

class IHelperWindowThread : public IRunnable {
public:

	virtual ~IHelperWindowThread() { }

	/**
	 * ��������� �����.
	 */
	virtual DWORD run()=0;

	/**
	 * ����� ������� ������ � �������� ���� ��������� ���������� ����.
	 * ����� �������� �����������, ������������ ����� ������������
	 * � ������� Event.
	 */
	virtual IHelperWindowController* getWindowController()=0;


};

	} // end namespace ddesvr
} // end namespace aquila