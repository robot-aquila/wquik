/**
 * ============================================================================
 * 2011/08/01
 * $Id: HelperWindowHandler.cpp 104 2011-08-15 09:47:48Z whirlwind $ Juno
 * ============================================================================
 */

#include "aquila/ddesvr/HelperWindowhandler.h"
#include "aquila/core/auto_drop.h"

using namespace aquila::core;

namespace aquila {
	namespace ddesvr {

HelperWindowHandler::HelperWindowHandler(IFactory* pInstanceFactory,
										 IServiceMap* pMap,
										 ICallbackHandler* pCallback)
  : instance(NULL),
	factory(pInstanceFactory),
	serviceMap(pMap),
	handler(pCallback)
{
}

HelperWindowHandler::~HelperWindowHandler() {
	if ( instance != NULL ) {
		instance->drop();
	}
}

void HelperWindowHandler::onBeforeCreate() {
	instance = factory->produce(handler, CP_WINANSI);
}

void HelperWindowHandler::onCreate() {
}

void HelperWindowHandler::onDestroy() {
}

void HelperWindowHandler::onAfterDestroy() {
	instance->drop();
	instance = NULL;
}

void HelperWindowHandler::onRegisterService(long serviceId) {
	auto_drop<IString> name
		(instance->createString(serviceMap->getName(serviceId)));
	instance->nameService(name, DNS_REGISTER);
}

void HelperWindowHandler::onUnregisterService(long serviceId) {
	auto_drop<IString> name
		(instance->createString(serviceMap->getName(serviceId)));
	instance->nameService(name, DNS_UNREGISTER);
}

IFactory* HelperWindowHandler::getInstanceFactory() {
	return factory;
}

IServiceMap* HelperWindowHandler::getServiceMap() {
	return serviceMap;
}

ICallbackHandler* HelperWindowHandler::getCallbackHandler() {
	return handler;
}

	} // end namespace ddesvr
} // end namespace aquila