/**
 * ============================================================================
 * 2011/08/01
 * $Id: CallbackDispatcher.h 104 2011-08-15 09:47:48Z whirlwind $ Juno
 * ============================================================================
 */
#pragma once
#include "aquila/dde/ICallbackHandler.h"
#include "aquila/ddesvr/IServiceMap.h"
#include "aquila/core/auto_grab.h"
#include "aquila/core/IEvent.h"

using namespace aquila::dde;
using namespace aquila::core;

namespace aquila {
	namespace ddesvr {

/**
 * Диспетчер обратных вызовов, используя карту сервисов перенаправляет вызовы,
 * поступающие от DDE, соответствующим обработчикам. Кроме этого, диспетчер
 * выполняет удаление соответствующей записи в карте сервисов после обработки
 * транзакции onUnregister.
 */
class CallbackDispatcher : public ICallbackHandler {
public:

	/**
	 * Конструктор.
	 * pServiceMap - экземпляр карты сервисов
	 * pEvent - экземпляр события используется для сигнализации отработки
	 * соответствующих методов при регистрации/дерегистрации сервисов.
	 */
	CallbackDispatcher(IServiceMap* pServiceMap, IEvent* pEvent);

	virtual ~CallbackDispatcher();

	/**
	 * Выполняет перенаправление соответствующему обработчику транзакций.
	 */
	bool onConnect(IString* topic, IString* service, PCONVCONTEXT pContext,
		bool isSameInstance);

	/**
	 * Выполняет перенаправление соответствующему обработчику транзакций.
	 */
	void onConnectConfirm(IConversation* conv, IString* topic,
		IString* service, bool isSameInstance);

	/**
	 * Выполняет перенаправление соответствующему обработчику транзакций.
	 */
	void onDisconnect(IConversation* conv, bool isSameInstance);

	/**
	 * Выполняет перенаправление соответствующему обработчику транзакций.
	 */
	int onPoke(UINT uFmt, IConversation* conv, IString* topic, IString* item,
		IData* data);

	/**
	 * Выполняет перенаправление соответствующему обработчику транзакций
	 * и сигнализирует о завершении отработки обработчика событием.
	 */
	void onRegister(IString* service, IString* instanceName);

	/**
	 * Выполняет перенаправление соответствующему обработчику транзакций,
	 * удаляет сервис из карты сервисов и сигнализирует о завершении отработки
	 * обработчика событием.
	 */
	void onUnregister(IString* service, IString* instanceName);

	/**
	 * Получить карту сервисов.
	 */
	IServiceMap* getServiceMap();

	/**
	 * Получить событие.
	 */
	IEvent* getEvent();

private:
	auto_grab<IServiceMap> serviceMap;
	auto_grab<IEvent> e;

};

	} // end namespace ddesvr
} // end namespace aquila