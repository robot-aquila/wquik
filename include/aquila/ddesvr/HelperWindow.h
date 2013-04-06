/**
 * ============================================================================
 * 2011/07/27
 * $Id: HelperWindow.h 104 2011-08-15 09:47:48Z whirlwind $
 * ============================================================================
 */

#pragma once
#pragma warning(disable:4290)
#include "aquila/core/auto_grab.h"
#include "aquila/core/IWinApi.h"
#include "aquila/ddesvr/IHelperWindow.h"
#include "aquila/ddesvr/IHelperWindowHandler.h"
#include "aquila/ddesvr/HelperWindowController.h"

using namespace aquila::core;

namespace aquila {
	namespace ddesvr {

#define HELPER_WINDOW_CLASS_NAME "aquila::core::HelperWindow[%x]"
/**
 * ���������� ���������������� ����. ��������������� ���� ������������ ���
 * ����������� ��������� ������� ���������, ��� ���������� ��� ������ DDE.
 */
class HelperWindow : public IHelperWindow {
public:

	/**
	 * �����������. ��� ������������.
	 *
	 * pWinApi - ��������� �������� ������� WinAPI.
	 * pWindowHandler - ���������� ������� ����.
	 */
	HelperWindow(IWinApi* pWinApi, IHelperWindowHandler* pWindowHandler);

	/**
	 * �����������. ��������.
	 */
	HelperWindow();

	/**
	 * ���������� �� ��������� ������������ ��������, ��� ��� ��� ���������
	 * ������� � ����������� ���������� ���������. ����� ������� �
	 * ������������� ���������� ������ ����������� ������ ������
	 * IHelperWindowController::close � ������������ �������� ����������
	 * ������, ��� ����� ����������������� � ���������� ���������� ������
	 * ���� � ������������ ���� ��������.
	 */
	virtual ~HelperWindow();

	void registerClass() throw (WinApiErrorException);

	IHelperWindowController* createWindow() throw (WinApiErrorException);

	void unregisterClass() throw (WinApiErrorException);

	void messageLoop() throw (WinApiErrorException);

	IWinApi* getWinApi();

	IHelperWindowHandler* getWindowHandler();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam,
									LPARAM lParam);

private:
	std::string getClassName();

	auto_grab<IWinApi> winApi;
	auto_grab<IHelperWindowHandler> handler;
	std::string className;

};

	} // end namespace ddesvr
} // end namespace aquila