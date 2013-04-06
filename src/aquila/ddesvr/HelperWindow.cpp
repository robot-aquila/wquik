/**
 * ============================================================================
 * 2011/07/28
 * $Id: HelperWindow.cpp 190 2012-01-30 18:34:54Z whirlwind $ Juno
 * ============================================================================
 */

#include "aquila/ddesvr/HelperWindow.h"
#include "aquila/core/auto_drop.h"
#include "aquila/core/WinApi.h"

using namespace aquila::core;

namespace aquila {
	namespace ddesvr {

HelperWindow::HelperWindow(IWinApi *pWinApi,
						   IHelperWindowHandler *pWindowHandler)
  : winApi(pWinApi),
    handler(pWindowHandler),
	className(getClassName())
{

}

std::string HelperWindow::getClassName() {
	char b[128];
	sprintf_s(b, sizeof(b), HELPER_WINDOW_CLASS_NAME, this);
	return b;
}

HelperWindow::~HelperWindow() {

}

IHelperWindowHandler* HelperWindow::getWindowHandler() {
	return handler;
}

IWinApi* HelperWindow::getWinApi() {
	return winApi;
}

void HelperWindow::registerClass() {
	WNDCLASS wc;
	::ZeroMemory(&wc, sizeof(wc));

	wc.lpfnWndProc = HelperWindow::WndProc;
	wc.lpszClassName = className.c_str();
	wc.hInstance = winApi->GetModuleHandle(NULL);
	if ( wc.hInstance == NULL ) {
		throw WinApiErrorException("GetModuleHandle failed", winApi);
	}
	if ( winApi->RegisterClass(&wc) == 0 ) {
		throw WinApiErrorException("RegisterClass failed", winApi);
	}
}

void HelperWindow::unregisterClass() {
	HINSTANCE hInstance = winApi->GetModuleHandle(NULL);
	if ( hInstance == NULL ) {
		throw WinApiErrorException("GetModuleHandle failed", winApi);
	}
	if ( ! winApi->UnregisterClass(className.c_str(), hInstance) ) {
		throw WinApiErrorException("UnregisterClass failed", winApi);
	}
}

IHelperWindowController* HelperWindow::createWindow() {
	CreateWindowEx_Args args;
	::ZeroMemory(&args, sizeof(args));
	args.lpClassName = className.c_str();
	args.lpWindowName = className.c_str();
	args.dwStyle = WS_OVERLAPPEDWINDOW;
	args.x = CW_USEDEFAULT;
	args.y = CW_USEDEFAULT;
	args.nWidth = CW_USEDEFAULT;
	args.nHeight = CW_USEDEFAULT;
	args.hWndParent = HWND_MESSAGE;
	args.hMenu = NULL;
	args.lpParam = (LPVOID)this;
	args.hInstance = winApi->GetModuleHandle(NULL);
	if ( args.hInstance == NULL ) {
		throw WinApiErrorException("GetModuleHandle failed", winApi);
	}
	HWND hWnd = winApi->CreateWindowEx(&args);
	if ( hWnd == NULL ) {
		throw WinApiErrorException("CreateWindowEx failed", winApi);
	}
	winApi->SetLastError(0);
	winApi->SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG)this);
	DWORD dwError = winApi->GetLastError();
	if ( dwError != 0 ) {
		winApi->DestroyWindow(hWnd);
		throw WinApiErrorException("SetWindowLongPtr failed", dwError);
	}
	return new HelperWindowController(winApi, hWnd);
}

void HelperWindow::messageLoop() {
	MSG msg;
	BOOL bRet;
	try {
		while( ( bRet = winApi->GetMessage( &msg, NULL, 0, 0 )) != 0 ) { 
			if ( bRet == -1 ) {
				break;
			} else {
				winApi->TranslateMessage(&msg); 
				winApi->DispatchMessage(&msg); 
			}
		}
	} catch ( std::exception e ) {
		printf("HelperWindow::messageLoop(): Unhandled exception: %s\n", e.what());
		throw e;
	} catch ( ... ) {
		printf("HelperWindow::messageLoop(): Unknown exception\n");
		throw;
	}
}

LRESULT HelperWindow::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	auto_drop<IWinApi> winApi(WinApi::getInstance());
	HelperWindow* pWin = NULL;
	switch ( uMsg ) {
	case WM_CREATE:
	case WM_NCCREATE:
	case WM_NCCALCSIZE:
		pWin = ((HelperWindow*)((CREATESTRUCT*)lParam)->lpCreateParams);
		break;
	default:
		pWin = (HelperWindow*)winApi->GetWindowLongPtr(hWnd, GWLP_USERDATA);
		break;
	}
	
	switch ( uMsg ) {
	case WM_NCCREATE:
		pWin->handler->onBeforeCreate();
		return TRUE;
	case WM_CREATE:
		pWin->handler->onCreate();
		return 0;
	case WM_HELPER_EXIT:
		pWin->handler->onDestroy();
		winApi->PostMessage(hWnd, WM_CLOSE, 0, 0);
		return 0;
	case WM_CLOSE:
		winApi->DestroyWindow(hWnd);
		return 0;
	case WM_NCDESTROY:
		pWin->handler->onAfterDestroy();
		winApi->PostQuitMessage(0);
		return 0;
	case WM_HELPER_REGISTER:
		pWin->handler->onRegisterService(lParam);
		return 0;
	case WM_HELPER_UNREGISTER:
		pWin->handler->onUnregisterService(lParam);
		return 0;
	default:
		return winApi->DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}

	} // end namespace ddesvr
} // end namespace aquila
