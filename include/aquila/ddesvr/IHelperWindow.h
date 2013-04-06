/**
 * ============================================================================
 * 2011/07/27
 * $Id: IHelperWindow.h 104 2011-08-15 09:47:48Z whirlwind $ Juno
 * ============================================================================
 */
#pragma once
#pragma warning(disable:4290)
#include <windows.h>
#include <exception>
#include "aquila/core/IReferenceCounted.h"
#include "aquila/core/WinApiErrorException.h"
#include "aquila/ddesvr/IHelperWindowController.h"

using namespace aquila::core;

namespace aquila {
	namespace ddesvr {

#define WM_HELPER_EXIT			WM_USER + 1
#define WM_HELPER_REGISTER		WM_USER + 2
#define WM_HELPER_UNREGISTER	WM_USER + 3

/**
 * ��������� ���������������� ����. ��������������� ���� ������������ ���
 * ����������� ��������� ������� ���������, ��� ���������� ��� ������ DDE.
 */
class IHelperWindow : public IReferenceCounted {
public:

	IHelperWindow() { }

	virtual ~IHelperWindow() { }

	/**
	 * ���������������� ����� ����.
	 * @throws WinApiErrorException - � ������ ������ WinAPI.
	 */
	virtual void registerClass() throw (WinApiErrorException)=0;

	/**
	 * ������� ��������� ����.
	 * @return ���������� ���������� ����.
	 * @throws WinApiErrorException - � ������ ������ WinAPI.
	 */
	virtual IHelperWindowController* createWindow()
		throw (WinApiErrorException)=0;

	/**
	 * ������� �����.
	 * @throws WinApiErrorException - � ������ ������ WinAPI.
	 */
	virtual void unregisterClass() throw (WinApiErrorException)=0;

	/**
	 * ����� � ���� ��������� ������� ���������.
	 * ��������: ����� ������� ������ �������� � ���������� ��������
	 * ������ �� ��������� ��������� ������� ��������� (�� ����, ��
	 * ��������� ��������� WM_QUIT).
	 * @throws WinApiErrorException - � ������ ������ WinAPI.
	 */
	virtual void messageLoop() throw (WinApiErrorException)=0;

};

	} // end namespace ddesvr
} // end namespace aquila