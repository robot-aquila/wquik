/**
 * ============================================================================
 * 2011/07/18
 * $Id: MockWinApi.h 104 2011-08-15 09:47:48Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/core/IWinApi.h"

namespace aquila {
	namespace core {

class MockWinApi : public IWinApi {
public:

	virtual ~MockWinApi() { }

	MOCK_METHOD0(createCriticalSection, ICriticalSection*());
	MOCK_METHOD4(createEvent, IEvent*(LPSECURITY_ATTRIBUTES pEventAttributes,
		BOOL bManualReset, BOOL bInitialState, LPCTSTR pName));
	MOCK_METHOD1(createMutex, IMutex*(const char* name));
	MOCK_METHOD1(createThread, IThread*(IRunnable* pThreadRunnable));

	MOCK_METHOD3(DdeAbandonTransaction, BOOL(DWORD idInst, HCONV hConv,
		DWORD idTransaction));

	MOCK_METHOD2(DdeAccessData, LPBYTE(HDDEDATA hData, LPDWORD pcbDataSize));

	MOCK_METHOD4(DdeAddData, HDDEDATA(HDDEDATA hData, LPBYTE pSrc, DWORD cb,
		DWORD cbOff));

	MOCK_METHOD8(DdeClientTransaction, HDDEDATA(LPBYTE pData, DWORD cbData,
		HCONV hConv, HSZ hszItem, UINT wFmt, UINT wType, DWORD dwTimeout,
		LPDWORD pdwResult));

	MOCK_METHOD2(DdeCmpStringHandles, int(HSZ hsz1, HSZ hsz2));

	MOCK_METHOD4(DdeConnect, HCONV(DWORD idInst, HSZ hszService, HSZ hszTopic,
		PCONVCONTEXT pCC));

	MOCK_METHOD5(DdeConnectList, HCONVLIST(DWORD idInst, HSZ hszService,
		HSZ hszTopic, HCONVLIST hConvList, PCONVCONTEXT pCC));

	MOCK_METHOD7(DdeCreateDataHandle, HDDEDATA(DWORD idInst, LPBYTE pSrc,
		DWORD cb, DWORD cbOff, HSZ hszItem, UINT wFmt, UINT afCmd));

	MOCK_METHOD3(DdeCreateStringHandle, HSZ(DWORD idInst, const char* psz,
			int iCodePage));

	MOCK_METHOD1(DdeDisconnect, BOOL(HCONV hConv));

	MOCK_METHOD1(DdeDisconnectList, BOOL(HCONVLIST hConvList));

	MOCK_METHOD3(DdeEnableCallback, BOOL(DWORD idInst, HCONV hConv,
		UINT wCmd));

	MOCK_METHOD1(DdeFreeDataHandle, BOOL(HDDEDATA hData));

	MOCK_METHOD2(DdeFreeStringHandle, BOOL(DWORD idInst, HSZ hsz));

	MOCK_METHOD4(DdeGetData, DWORD(HDDEDATA hData, LPBYTE pDst, DWORD cbMax,
		DWORD cbOff));

	MOCK_METHOD1(DdeGetLastError, UINT(DWORD idInst));

	MOCK_METHOD1(DdeImpersonateClient, BOOL(HCONV hConv));

	MOCK_METHOD4(DdeInitialize, UINT(LPDWORD pidInst, PFNCALLBACK pfnCallback,
		DWORD afCmd, DWORD ulRes));

	MOCK_METHOD2(DdeKeepStringHandle, BOOL(DWORD idInst, HSZ hsz));

	MOCK_METHOD4(DdeNameService, HDDEDATA(DWORD idInst, HSZ hsz1, HSZ hsz2,
		UINT afCmd));

	MOCK_METHOD3(DdePostAdvise, BOOL(DWORD idInst, HSZ hszTopic, HSZ hszItem));

	MOCK_METHOD3(DdeQueryConvInfo, UINT(HCONV hConv, DWORD idTransaction,
		PCONVINFO pConvInfo));

	MOCK_METHOD2(DdeQueryNextServer, HCONV(HCONVLIST hConvList,
		HCONV hConvPrev));

	MOCK_METHOD5(DdeQueryString, DWORD(DWORD idInst, HSZ hsz, char* psz,
		DWORD cchMax, int iCodePage));

	MOCK_METHOD1(DdeReconnect, HCONV(HCONV hConv));

	MOCK_METHOD3(DdeSetUserHandle, BOOL(HCONV hConv, DWORD id,
		DWORD_PTR hUser));

	MOCK_METHOD1(DdeUnaccessData, BOOL(HDDEDATA hData));

	MOCK_METHOD1(DdeUninitialize, BOOL(DWORD idInst));

	MOCK_METHOD1(InitializeCriticalSection, void(LPCRITICAL_SECTION pCs));

	MOCK_METHOD1(DeleteCriticalSection, void(LPCRITICAL_SECTION pCs));

	MOCK_METHOD1(EnterCriticalSection, void(LPCRITICAL_SECTION pCs));

	MOCK_METHOD1(LeaveCriticalSection, void(LPCRITICAL_SECTION pCs));

	MOCK_METHOD6(CreateThread, HANDLE(LPSECURITY_ATTRIBUTES pAttributes,
		SIZE_T dwStackSize, LPTHREAD_START_ROUTINE pStartAddress,
		LPVOID pParam, DWORD dwCreationFlags, LPDWORD pThreadId));

	MOCK_METHOD1(CloseHandle, BOOL(HANDLE hObject));

	MOCK_METHOD2(GetExitCodeThread, BOOL(HANDLE hThread, LPDWORD lpExitCode));

	MOCK_METHOD2(WaitForSingleObject, DWORD(HANDLE hHandle,
		DWORD dwMilliseconds));

	MOCK_METHOD4(WaitForMultipleObjects, DWORD(DWORD nCount,
		HANDLE* lpHandler, BOOL bWaitAll, DWORD dwMilliseconds));

	MOCK_METHOD4(CreateEvent, HANDLE(LPSECURITY_ATTRIBUTES lpEventAttributes,
		BOOL bManualReset, BOOL bInitialState, LPCSTR lpName));

	MOCK_METHOD1(SetEvent, BOOL(HANDLE hEvent));

	MOCK_METHOD1(ResetEvent, BOOL(HANDLE hEvent));

	MOCK_METHOD1(PulseEvent, BOOL(HANDLE hEvent));

	MOCK_METHOD0(GetLastError, DWORD());

	MOCK_METHOD1(SetLastError, void(DWORD dwErrorCode));

	MOCK_METHOD1(GetModuleHandle, HMODULE(LPCSTR lpModuleName));

	MOCK_METHOD1(RegisterClass, ATOM(WNDCLASS* pwc));

	MOCK_METHOD1(CreateWindowEx, HWND(CreateWindowEx_Args* pArgs));

	MOCK_METHOD3(SetWindowLongPtr, LONG_PTR(HWND hWnd, int nIndex,
		LONG_PTR dwNewLong));

	MOCK_METHOD2(GetWindowLongPtr, LONG_PTR(HWND hWnd, int nIndex));


	MOCK_METHOD1(DestroyWindow, BOOL(HWND hWnd));

	MOCK_METHOD2(UnregisterClass, BOOL(LPCSTR lpClassName,
		HINSTANCE hInstance));

	MOCK_METHOD4(GetMessage, BOOL(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin,
			UINT wMsgFilterMax));

	MOCK_METHOD1(TranslateMessage, BOOL(const MSG* lpMsg));

	MOCK_METHOD1(DispatchMessage, LRESULT(const MSG* lpmsg));

	MOCK_METHOD4(DefWindowProc, LRESULT(HWND hWnd, UINT Msg, WPARAM wParam,
		LPARAM lParam));

	MOCK_METHOD4(PostMessage, BOOL(HWND hWnd, UINT uMsg, WPARAM wParam,
		LPARAM lParam));

	MOCK_METHOD1(PostQuitMessage, void(int nExitCode));

	MOCK_METHOD4(SendMessage, LRESULT(HWND hWnd, UINT uMsg, WPARAM wParam,
		LPARAM lParam));

};

	} // end namespace core
} // end namespace aquila