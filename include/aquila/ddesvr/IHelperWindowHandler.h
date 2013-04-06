/**
 * ============================================================================
 * 2011/07/27
 * $Id: IHelperWindowHandler.h 101 2011-08-11 18:37:57Z whirlwind $ Juno
 * ============================================================================
 */
#pragma once
#include "aquila/core/IReferenceCounted.h"

using namespace aquila::core;

namespace aquila {
	namespace ddesvr {

/**
 * Интерфейс обработчика событий вспомогательного окна.
 * Все вызовы методов осуществляются из отдельного потока, что позволяет
 * организовать нормальную работу всех функций DDE в соответствии с
 * требованиями WinAPI.
 */
class IHelperWindowHandler : public IReferenceCounted {
public:

	IHelperWindowHandler() { }

	virtual ~IHelperWindowHandler() { }

	/**
	 * Метод вызывается в момент создания окна (реакция на WM_NCCREATE).
	 * Данный метод используется для создания инстанса DDE.
	 */
	virtual void onBeforeCreate()=0;

	/**
	 * Метод вызывается в момент создания окна (реакция на WM_CREATE).
	 * В базовой реализации здесь может осуществляться вызов DdeNameService
	 * для известных имен сервисов.
	 */
	virtual void onCreate()=0;

	/**
	 * Метод вызывается перед завершением работы окна. Этот вызов
	 * осуществляется до обработки WM_NCDESTROY и даже до обработки WM_CLOSE.
	 * Это сделано для того, что бы получить возможность обработать
	 * XTYP_UNREGISTER в обработчике транзакций DDE.
	 */
	virtual void onDestroy()=0;

	/**
	 * Метод вызывается после уничтожения окна.
	 * Здесь все занятые объекты должны быть освобождены.
	 */
	virtual void onAfterDestroy()=0;

	/**
	 * Метод вызывается как реакция на запрос о регистрации нового сервиса.
	 * @param serviceId - идентификатор сервиса
	 */
	virtual void onRegisterService(long serviceId)=0;

	/**
	 * Метод вызывается как реакция на запрос об удалении сервиса.
	 * @param serviceId - идентификатор сервиса
	 */
	virtual void onUnregisterService(long serviceId)=0;

};

	} // end namespace ddesvr
} // end namespace aquila