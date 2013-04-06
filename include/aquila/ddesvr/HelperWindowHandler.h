/**
 * ============================================================================
 * 2011/08/01
 * $Id: HelperWindowHandler.h 235 2012-07-23 15:52:48Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#include "aquila/core/auto_grab.h"
#include "aquila/dde/IFactory.h"
#include "aquila/ddesvr/IHelperWindowHandler.h"
#include "aquila/ddesvr/IServiceMap.h"

using namespace aquila::dde;

namespace aquila {
	namespace ddesvr {

/**
 * Обработчик событий вспомогательного окна транслирует события в вызовы
 * соответствующих функций DDE. Подразумевается работа в одном потоке, то есть
 * Не является потокобезопасным.
 */
class HelperWindowHandler : public IHelperWindowHandler {
public:

	/**
	 * pInstanceFactory - фабрика DDE-инстанса.
	 * pMap - карта сервисов используется для реализации реакции на вызов
	 * onRegisterService, onUnregisterService и для конструкции диспетчера
	 * транзакций.
	 * pCallback - обработчик DDE-транзакций используется для инстанцирования
	 * DDE-экземпляра.
	 */
	HelperWindowHandler(IFactory* pInstanceFactory,
						IServiceMap* pMap,
						ICallbackHandler* pCallback);

	virtual ~HelperWindowHandler();

	/**
	 * Реакцией на вызов является создание экземпляра DDE.
	 */
	void onBeforeCreate();

	void onCreate();

	/**
	 * Реакцией на вызов является удаление всех зарегистрированных в карте
	 * сервисов.
	 */
	void onDestroy();

	/**
	 * Реакцией на вызов является удаление экземпляра DDE.
	 */
	void onAfterDestroy();

	/**
	 * Реакцией на вызов является вызов DdeNameService для регистрации
	 * сервиса, имя которого соответствует указанному идентификатору в карте.
	 */
	void onRegisterService(long serviceId);

	/**
	 * Реакцией на вызов является вызов DdeNameService для дерегистрации
	 * сервиса, имя которого соответствует указанному идентификатору в карте.
	 */
	void onUnregisterService(long serviceId);

	IFactory* getInstanceFactory();

	IServiceMap* getServiceMap();

	ICallbackHandler* getCallbackHandler();

#ifdef TEST_RUN
	void setInstance(IInstance* pInstance) {
		instance = pInstance;
	}

	IInstance* getInstance() {
		return instance;
	}
#else
#pragma message("Set TEST_RUN definition to enable additional method(s):")
#pragma message("aquila::ddesvr::HelperWindowHandler::setInstance")
#pragma message("aquila::ddesvr::HelperWindowHandler::getInstance")
#endif

private:
	IInstance* instance;
	auto_grab<IFactory> factory;
	auto_grab<IServiceMap> serviceMap;
	auto_grab<ICallbackHandler> handler;

};

	} // end namespace ddesvr
} // end namespace aquila