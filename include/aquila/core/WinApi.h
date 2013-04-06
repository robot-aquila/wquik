/**
 * ============================================================================
 * 2011/07/21
 * $Id: WinApi.h 104 2011-08-15 09:47:48Z whirlwind $ Juno
 * Объектная обертка функций WinAPI.
 * ============================================================================
 */

#pragma once
#include "aquila/core/IWinApi.h"
#include "aquila/core/Mutex.h"
#include "aquila/core/CriticalSection.h"
#include "aquila/core/Event.h"
#include "aquila/core/Thread.h"

namespace aquila {
	namespace core {

#define WINAPI_WRAPPER_MUTEX "WINAPI_WRAPPER_MUTEX"

class WinApi : public IWinApi {
private:

	WinApi() {
		
	}

public:

	/**
	 * Данный метод возвращает указатель на установленный экземпляр оболочки
	 * функций WinAPI с увеличением счетчика ссылок на единицу. Если текущий
	 * экземпляр оболочки не определен, то метод инстанцирует экземпляр
	 * класса WinApi. Каждый вызов этого метода увеличивает счетчик ссылок
	 * установленного экземпляра на единицу. То есть для хранения результата
	 * вызова следует использовать auto_drop указатель.
	 */
	static IWinApi* getInstance();


	/**
	 * Позволяет установить указатель на экземпляр оболочки функций WinAPI.
	 * Используется в основном для тестов. Если в момент вызова указатель
	 * на текущий экземпляр оболочки уже определен, то он будет перезаписан.
	 * Экземпляр сохраняется как есть без увеличения счетчика ссылок.
	 * ВНИМАНИЕ: Если в качестве экземпляра обертки используется класс,
	 * отличный от данного, то при уничтожении этого экземпляра локальный
	 * указатель не будет очищен, что приведет к фатальной ошибке в случае
	 * последующего вызова метода getInstance. Чтобы избежать этого,
	 * следует использовать setInstance с нулевым указателем при/после
	 * уничтожения объекта класса этой другой реализации.
	 */
	static void setInstance(IWinApi* pWinApi);

	/**
	 * Деструктор автоматически сбрасывает указатель на экземпляр оболочки,
	 * если она установлена в качестве текущей.
	 */
	virtual ~WinApi();

	ICriticalSection* createCriticalSection() {
		return new CriticalSection(this);
	}

	IEvent* createEvent(LPSECURITY_ATTRIBUTES pEventAttributes,
		BOOL bManualReset, BOOL bInitialState, LPCTSTR pName)
	{
		return new Event(this, pEventAttributes, bManualReset,
			bInitialState, pName);
	}

	IMutex* createMutex(const char* name) {
		return new Mutex(name);
	}

	IThread* createThread(IRunnable* pThreadRunnable) {
		return new Thread(this, createCriticalSection(), pThreadRunnable);
	}

	BOOL DdeAbandonTransaction(DWORD idInst, HCONV hConv,
		DWORD idTransaction)
	{
		return ::DdeAbandonTransaction(idInst, hConv, idTransaction);
	}

	LPBYTE DdeAccessData(HDDEDATA hData, LPDWORD pcbDataSize) {
		return ::DdeAccessData(hData, pcbDataSize);
	}

	HDDEDATA DdeAddData(HDDEDATA hData, LPBYTE pSrc, DWORD cb, DWORD cbOff) {
		return ::DdeAddData(hData, pSrc, cb, cbOff);
	}

	HDDEDATA DdeClientTransaction(LPBYTE pData, DWORD cbData, HCONV hConv,
		HSZ hszItem, UINT wFmt, UINT wType, DWORD dwTimeout, LPDWORD pdwResult)
	{
		return ::DdeClientTransaction(pData, cbData, hConv, hszItem, wFmt,
			wType, dwTimeout, pdwResult);
	}

	int DdeCmpStringHandles(HSZ hsz1, HSZ hsz2) {
		return ::DdeCmpStringHandles(hsz1, hsz2);
	}

	HCONV DdeConnect(DWORD idInst, HSZ hszService, HSZ hszTopic,
		PCONVCONTEXT pCC)
	{
		return ::DdeConnect(idInst, hszService, hszTopic, pCC);
	}


	HCONVLIST DdeConnectList(DWORD idInst, HSZ hszService, HSZ hszTopic,
		HCONVLIST hConvList, PCONVCONTEXT pCC)
	{
		return ::DdeConnectList(idInst, hszService, hszTopic, hConvList, pCC);
	}

	HDDEDATA DdeCreateDataHandle(DWORD idInst, LPBYTE pSrc, DWORD cb,
		DWORD cbOff, HSZ hszItem, UINT wFmt, UINT afCmd)
	{
		return ::DdeCreateDataHandle(idInst, pSrc, cb, cbOff, hszItem,
			wFmt, afCmd);
	}

	HSZ DdeCreateStringHandle(DWORD idInst, const char* psz, int iCodePage) {
		return::DdeCreateStringHandle(idInst, psz, iCodePage);
	}

	BOOL DdeDisconnect(HCONV hConv) {
		return ::DdeDisconnect(hConv);
	}

	BOOL DdeDisconnectList(HCONVLIST hConvList) {
		return ::DdeDisconnectList(hConvList);
	}

	BOOL DdeEnableCallback(DWORD idInst, HCONV hConv, UINT wCmd) {
		return ::DdeEnableCallback(idInst, hConv, wCmd);
	}

	BOOL DdeFreeDataHandle(HDDEDATA hData) {
		return ::DdeFreeDataHandle(hData);
	}

	BOOL DdeFreeStringHandle(DWORD idInst, HSZ hsz) {
		return ::DdeFreeStringHandle(idInst, hsz);
	}

	DWORD DdeGetData(HDDEDATA hData, LPBYTE pDst, DWORD cbMax, DWORD cbOff) {
		return ::DdeGetData(hData, pDst, cbMax, cbOff);
	}

	UINT DdeGetLastError(DWORD idInst) {
		return ::DdeGetLastError(idInst);
	}

	BOOL DdeImpersonateClient(HCONV hConv) {
		return ::DdeImpersonateClient(hConv);
	}

	UINT DdeInitialize(LPDWORD pidInst, PFNCALLBACK pfnCallback, DWORD afCmd,
		DWORD ulRes)
	{
		return ::DdeInitialize(pidInst, pfnCallback, afCmd, ulRes);
	}

	BOOL DdeKeepStringHandle(DWORD idInst, HSZ hsz) {
		return ::DdeKeepStringHandle(idInst, hsz);
	}

	HDDEDATA DdeNameService(DWORD idInst, HSZ hsz1, HSZ hsz2, UINT afCmd) {
		return ::DdeNameService(idInst, hsz1, hsz2, afCmd);
	}

	BOOL DdePostAdvise(DWORD idInst, HSZ hszTopic, HSZ hszItem) {
		return ::DdePostAdvise(idInst, hszTopic, hszItem);
	}

	UINT DdeQueryConvInfo(HCONV hConv, DWORD idTransaction,
		PCONVINFO pConvInfo)
	{
		return ::DdeQueryConvInfo(hConv, idTransaction, pConvInfo);
	}

	HCONV DdeQueryNextServer(HCONVLIST hConvList, HCONV hConvPrev) {
		return ::DdeQueryNextServer(hConvList, hConvPrev);
	}

	DWORD DdeQueryString(DWORD idInst, HSZ hsz, char* psz, DWORD cchMax,
		int iCodePage) 
	{
		return ::DdeQueryString(idInst, hsz, psz, cchMax, iCodePage);
	}

	HCONV DdeReconnect(HCONV hConv) {
		return ::DdeReconnect(hConv);
	}

	BOOL DdeSetUserHandle(HCONV hConv, DWORD id, DWORD_PTR hUser) {
		return ::DdeSetUserHandle(hConv, id, hUser);
	}

	BOOL DdeUnaccessData(HDDEDATA hData) {
		return ::DdeUnaccessData(hData);
	}

	BOOL DdeUninitialize(DWORD idInst) {
		return ::DdeUninitialize(idInst);
	}

	void InitializeCriticalSection(LPCRITICAL_SECTION pCs) {
		::InitializeCriticalSection(pCs);
	}

	void DeleteCriticalSection(LPCRITICAL_SECTION pCs) {
		::DeleteCriticalSection(pCs);
	}

	void EnterCriticalSection(LPCRITICAL_SECTION pCs) {
		::EnterCriticalSection(pCs);
	}

	void LeaveCriticalSection(LPCRITICAL_SECTION pCs) {
		::LeaveCriticalSection(pCs);
	}

	HANDLE CreateThread(LPSECURITY_ATTRIBUTES pAttributes, SIZE_T dwStackSize,
			LPTHREAD_START_ROUTINE pStartAddress, LPVOID pParam,
			DWORD dwCreationFlags, LPDWORD pThreadId)
	{
		return ::CreateThread(pAttributes, dwStackSize, pStartAddress, pParam,
			dwCreationFlags, pThreadId);
	}

	BOOL CloseHandle(HANDLE hObject) {
		return ::CloseHandle(hObject);
	}

	BOOL GetExitCodeThread(HANDLE hThread, LPDWORD lpExitCode) {
		return ::GetExitCodeThread(hThread, lpExitCode);
	}

	DWORD WaitForSingleObject(HANDLE hHandle, DWORD dwMilliseconds) {
		return ::WaitForSingleObject(hHandle, dwMilliseconds);
	}

	DWORD WaitForMultipleObjects(DWORD nCount, HANDLE* lpHandles,
		BOOL bWaitAll, DWORD dwMilliseconds)
	{
		return ::WaitForMultipleObjects(nCount, lpHandles,
			bWaitAll, dwMilliseconds);
	}

	HANDLE CreateEvent(LPSECURITY_ATTRIBUTES lpEventAttributes,
			BOOL bManualReset, BOOL bInitialState, LPCSTR lpName)
	{
		return ::CreateEvent(lpEventAttributes, bManualReset, bInitialState,
			lpName);
	}

	BOOL SetEvent(HANDLE hEvent) {
		return ::SetEvent(hEvent);
	}

	BOOL ResetEvent(HANDLE hEvent) {
		return ::ResetEvent(hEvent);
	}

	BOOL PulseEvent(HANDLE hEvent) {
		return ::PulseEvent(hEvent);
	}

	DWORD GetLastError() {
		return ::GetLastError();
	}

	void SetLastError(DWORD dwErrorCode) {
		::SetLastError(dwErrorCode);
	}

	HMODULE GetModuleHandle(LPCSTR lpModuleName) {
		return ::GetModuleHandle(lpModuleName);
	}

	ATOM RegisterClass(WNDCLASS* pwc) {
		return ::RegisterClass(pwc);
	}
	
	HWND CreateWindowEx(CreateWindowEx_Args* pArgs) {
		return ::CreateWindowEx(pArgs->dwExStyle,
								pArgs->lpClassName,
								pArgs->lpWindowName,
								pArgs->dwStyle,
								pArgs->x,
								pArgs->y,
								pArgs->nWidth,
								pArgs->nHeight,
								pArgs->hWndParent,
								pArgs->hMenu,
								pArgs->hInstance,
								pArgs->lpParam);
	}

	LONG_PTR SetWindowLongPtr(HWND hWnd, int nIndex, LONG_PTR dwNewLong) {
		return ::SetWindowLongPtr(hWnd, nIndex, dwNewLong);
	}

	LONG_PTR GetWindowLongPtr(HWND hWnd, int nIndex) {
		return ::GetWindowLongPtr(hWnd, nIndex);
	}

	BOOL DestroyWindow(HWND hWnd) {
		return::DestroyWindow(hWnd);
	}

	BOOL UnregisterClass(LPCSTR lpClassName, HINSTANCE hInstance) {
		return ::UnregisterClass(lpClassName, hInstance);
	}

	BOOL GetMessage(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin,
		UINT wMsgFilterMax)
	{
		return ::GetMessage(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax);
	}

	BOOL TranslateMessage(const MSG* lpMsg) {
		return ::TranslateMessage(lpMsg);
	}

	LRESULT DispatchMessage(const MSG* lpmsg) {
		return ::DispatchMessage(lpmsg);
	}

	LRESULT DefWindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
		return ::DefWindowProc(hWnd, Msg, wParam, lParam);
	}

	BOOL PostMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		return ::PostMessage(hWnd, uMsg, wParam, lParam);
	}

	void PostQuitMessage(int nExitCode) {
		return ::PostQuitMessage(nExitCode);
	}

	LRESULT SendMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		return ::SendMessage(hWnd, uMsg, wParam, lParam);
	}

};

	} // end namespace core
} // end namespace aquila

