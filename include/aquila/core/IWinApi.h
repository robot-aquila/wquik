/**
 * ============================================================================
 * 2011/07/21
 * $Id: IWinApi.h 104 2011-08-15 09:47:48Z whirlwind $ Juno
 * Интерфейс обертки функций WinAPI.
 * Так же данный интерфейс определяет некоторые фабричные методы для
 * экземпляров-оберток некоторых объектов Windows.
 * ============================================================================
 */

#pragma once
#include <windows.h>
#include "aquila/core/IReferenceCounted.h"

namespace aquila {
	namespace core {

class ICriticalSection;
class IEvent;
class IMutex;
class IThread;
class IRunnable;

/**
 * Googlemock не позволяет мокать методы с количеством аргументов более 10.
 * Данная структура используется для передачи параметров вызова CreateWindowEx.
 */
typedef struct {
	DWORD dwExStyle;
	LPCSTR lpClassName;
	LPCSTR lpWindowName;
	DWORD dwStyle;
	int x;
	int y;
	int nWidth;
	int nHeight;
	HWND hWndParent;
	HMENU hMenu;
	HINSTANCE hInstance;
	LPVOID lpParam;
} CreateWindowEx_Args;

class IWinApi : public IReferenceCounted {
public:
	virtual ~IWinApi() { }

	virtual ICriticalSection* createCriticalSection()=0;
	virtual IEvent* createEvent(LPSECURITY_ATTRIBUTES pEventAttributes,
		BOOL bManualReset, BOOL bInitialState, LPCTSTR pName)=0;
	virtual IMutex* createMutex(const char* name)=0;
	virtual IThread* createThread(IRunnable* pThreadRunnable)=0;

	virtual BOOL
		DdeAbandonTransaction(DWORD idInst, HCONV hConv,
			DWORD idTransaction)=0;

	virtual LPBYTE
		DdeAccessData(HDDEDATA hData, LPDWORD pcbDataSize)=0;

	virtual HDDEDATA
		DdeAddData(HDDEDATA hData, LPBYTE pSrc, DWORD cb, DWORD cbOff)=0;

	virtual HDDEDATA
		DdeClientTransaction(LPBYTE pData, DWORD cbData, HCONV hConv,
			HSZ hszItem, UINT wFmt, UINT wType, DWORD dwTimeout,
			LPDWORD pdwResult)=0;

	virtual int
		DdeCmpStringHandles(HSZ hsz1, HSZ hsz2)=0;

	virtual HCONV
		DdeConnect(DWORD idInst, HSZ hszService, HSZ hszTopic,
			PCONVCONTEXT pCC)=0;

	virtual HCONVLIST
		DdeConnectList(DWORD idInst, HSZ hszService,
			HSZ hszTopic, HCONVLIST hConvList, PCONVCONTEXT pCC)=0;

	virtual HDDEDATA
		DdeCreateDataHandle(DWORD idInst, LPBYTE pSrc, DWORD cb, DWORD cbOff,
			HSZ hszItem, UINT wFmt, UINT afCmd)=0;

	virtual HSZ
		DdeCreateStringHandle(DWORD idInst, const char* psz, int iCodePage)=0;

	virtual BOOL
		DdeDisconnect(HCONV hConv)=0;

	virtual BOOL
		DdeDisconnectList(HCONVLIST hConvList)=0;

	virtual BOOL
		DdeEnableCallback(DWORD idInst, HCONV hConv, UINT wCmd)=0;

	virtual BOOL
		DdeFreeDataHandle(HDDEDATA hData)=0;

	virtual BOOL
		DdeFreeStringHandle(DWORD idInst, HSZ hsz)=0;

	virtual DWORD
		DdeGetData(HDDEDATA hData, LPBYTE pDst, DWORD cbMax, DWORD cbOff)=0;

	virtual UINT
		DdeGetLastError(DWORD idInst)=0;

	virtual BOOL
		DdeImpersonateClient(HCONV hConv)=0;

	virtual UINT
		DdeInitialize(LPDWORD pidInst, PFNCALLBACK pfnCallback, DWORD afCmd,
			DWORD ulRes)=0;

	virtual BOOL
		DdeKeepStringHandle(DWORD idInst, HSZ hsz)=0;

	virtual HDDEDATA
		DdeNameService(DWORD idInst, HSZ hsz1, HSZ hsz2, UINT afCmd)=0;

	virtual BOOL
		DdePostAdvise(DWORD idInst, HSZ hszTopic, HSZ hszItem)=0;

	virtual UINT
		DdeQueryConvInfo(HCONV hConv, DWORD idTransaction,
			PCONVINFO pConvInfo)=0;

	virtual HCONV
		DdeQueryNextServer(HCONVLIST hConvList, HCONV hConvPrev)=0;

	virtual DWORD
		DdeQueryString(DWORD idInst, HSZ hsz, char* psz, DWORD cchMax,
			int iCodePage)=0;

	virtual HCONV
		DdeReconnect(HCONV hConv)=0;

	virtual BOOL
		DdeSetUserHandle(HCONV hConv, DWORD id, DWORD_PTR hUser)=0;

	virtual BOOL
		DdeUnaccessData(HDDEDATA hData)=0;

	virtual BOOL
		DdeUninitialize(DWORD idInst)=0;

	virtual void
		InitializeCriticalSection(LPCRITICAL_SECTION pCs)=0;

	virtual void
		DeleteCriticalSection(LPCRITICAL_SECTION pCs)=0;

	virtual void
		EnterCriticalSection(LPCRITICAL_SECTION pCs)=0;

	virtual void
		LeaveCriticalSection(LPCRITICAL_SECTION pCs)=0;
	
	virtual HANDLE
		CreateThread(LPSECURITY_ATTRIBUTES pAttributes, SIZE_T dwStackSize,
			LPTHREAD_START_ROUTINE pStartAddress, LPVOID pParam,
			DWORD dwCreationFlags, LPDWORD pThreadId)=0;

	virtual BOOL
		CloseHandle(HANDLE hObject)=0;

	virtual BOOL
		GetExitCodeThread(HANDLE hThread, LPDWORD lpExitCode)=0;

	virtual DWORD
		WaitForSingleObject(HANDLE hHandle, DWORD dwMilliseconds)=0;

	virtual DWORD
		WaitForMultipleObjects(DWORD nCount, HANDLE* lpHandles,
		BOOL bWaitAll, DWORD dwMilliseconds)=0;

	virtual HANDLE
		CreateEvent(LPSECURITY_ATTRIBUTES lpEventAttributes, BOOL bManualReset,
			BOOL bInitialState, LPCSTR lpName)=0;

	virtual BOOL
		SetEvent(HANDLE hEvent)=0;

	virtual BOOL
		ResetEvent(HANDLE hEvent)=0;

	virtual BOOL
		PulseEvent(HANDLE hEvent)=0;

	virtual DWORD
		GetLastError()=0;

	virtual void
		SetLastError(DWORD dwErrorCode)=0;

	virtual HMODULE
		GetModuleHandle(LPCSTR lpModuleName)=0;

	virtual ATOM
		RegisterClass(WNDCLASS* pwc)=0;
	
	virtual HWND
		CreateWindowEx(CreateWindowEx_Args* pArgs)=0;

	virtual LONG_PTR
		SetWindowLongPtr(HWND hWnd, int nIndex, LONG_PTR dwNewLong)=0;

	virtual LONG_PTR
		GetWindowLongPtr(HWND hWnd, int nIndex)=0;

	virtual BOOL
		DestroyWindow(HWND hWnd)=0;

	virtual BOOL
		UnregisterClass(LPCSTR lpClassName, HINSTANCE hInstance)=0;

	virtual BOOL
		GetMessage(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin,
			UINT wMsgFilterMax)=0;

	virtual BOOL
		TranslateMessage(const MSG* lpMsg)=0;

	virtual LRESULT
		DispatchMessage(const MSG* lpmsg)=0;

	virtual LRESULT
		DefWindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)=0;

	virtual BOOL
		PostMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)=0;

	virtual void
		PostQuitMessage(int nExitCode)=0;

	virtual LRESULT
		SendMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)=0;

};

	} // end namespace core
} // end namespace aquila