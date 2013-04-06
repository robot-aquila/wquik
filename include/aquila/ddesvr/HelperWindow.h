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
 * Реализация вспомогательного окна. Вспомогательное окно используется для
 * организации обработки очереди сообщений, что необходимо для работы DDE.
 */
class HelperWindow : public IHelperWindow {
public:

	/**
	 * Конструктор. Для тестирования.
	 *
	 * pWinApi - экземпляр оболочки функций WinAPI.
	 * pWindowHandler - обработчик событий окна.
	 */
	HelperWindow(IWinApi* pWinApi, IHelperWindowHandler* pWindowHandler);

	/**
	 * Конструктор. Основной.
	 */
	HelperWindow();

	/**
	 * Дескриптор не выполняет освобождения ресурсов, так как эта процедура
	 * связана с асинхронной обработкой сообщений. Важно помнить о
	 * необходимости завершения работы посредством вызова метода
	 * IHelperWindowController::close и последующего ожидания завершения
	 * потока, что будет свидетельствовать о нормальном завершении работы
	 * окна и освобождении всех ресурсов.
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