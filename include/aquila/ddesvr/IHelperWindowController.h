/**
 * ============================================================================
 * 2011/07/27
 * $Id: IHelperWindowController.h 101 2011-08-11 18:37:57Z whirlwind $ Juno
 * ============================================================================
 */
#pragma once
#pragma warning(disable:4290)
#include <windows.h>
#include "aquila/core/IReferenceCounted.h"
#include "aquila/core/WinApiErrorException.h"

using namespace aquila::core;

namespace aquila {
	namespace ddesvr {

/**
 * Интерфейс контроллера вспомогательного окна. Контроллер используется
 * для управления вспомогательным окном.
 */
class IHelperWindowController : public IReferenceCounted {
public:

	IHelperWindowController() { }

	virtual ~IHelperWindowController() { }

	/**
	 * Зарегистрировать сервис с указаным идентификатором.
	 * Данный метод инициирует вызов метода onRegisterService обработчика
	 * событий окна. Этот метод может быть вызван из любого потока,
	 * но обработка события будет выполнена в потоке окна, что позволяет
	 * соблюдать условие "все вызовы из одного потока", предъявляемые
	 * библиотекой DDE.
	 * @serviceId - идентификатор сервиса
	 * @throws WinApiErrorException - в случае ошибки WinAPI
	 */
	virtual void
		registerService(long serviceId) throw (WinApiErrorException)=0;

	/**
	 * Удалить сервис с указанным идентификаторов.
	 * Данный метод инициирует вызов метода onUnregisterService обработчика
	 * событий окна. Так же как и метод регистрации сервиса, этот метод может
	 * быть вызван из любого потока.
	 * @serviceId - идентификатор сервиса
	 * @throws WinApiErrorException - в случае ошибки WinAPI
	 */
	virtual void
		unregisterService(long serviceId) throw (WinApiErrorException)=0;

	/**
	 * Завершить работу.
	 * Вызов данного метода инициирует отправку сообщения о необходимости
	 * начать процедуру завершения работы вспомогательного окна. Этот метод
	 * может быть вызван из любого потока.
	 * @throws WinApiErrorException - ошибка отправки сообщения
	 * @throws HelperWindowException - работа окна не начата
	 */
	virtual void close() throw (WinApiErrorException)=0;

};

	} // end namespace ddesvr
} // end namespace aquila