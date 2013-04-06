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
 * Интерфейс вспомогательного окна. Вспомогательное окно используется для
 * организации обработки очереди сообщений, что необходимо для работы DDE.
 */
class IHelperWindow : public IReferenceCounted {
public:

	IHelperWindow() { }

	virtual ~IHelperWindow() { }

	/**
	 * Зарегистрировать класс окна.
	 * @throws WinApiErrorException - в случае ошибки WinAPI.
	 */
	virtual void registerClass() throw (WinApiErrorException)=0;

	/**
	 * Создать экземпляр окна.
	 * @return контроллер созданного окна.
	 * @throws WinApiErrorException - в случае ошибки WinAPI.
	 */
	virtual IHelperWindowController* createWindow()
		throw (WinApiErrorException)=0;

	/**
	 * Удалить класс.
	 * @throws WinApiErrorException - в случае ошибки WinAPI.
	 */
	virtual void unregisterClass() throw (WinApiErrorException)=0;

	/**
	 * Войти в цикл обработки очереди сообщений.
	 * ВНИМАНИЕ: Вызов данного метода приводит к блокировке текущего
	 * потока до окончания обработки очереди сообщений (то есть, до
	 * получения сообщения WM_QUIT).
	 * @throws WinApiErrorException - в случае ошибки WinAPI.
	 */
	virtual void messageLoop() throw (WinApiErrorException)=0;

};

	} // end namespace ddesvr
} // end namespace aquila