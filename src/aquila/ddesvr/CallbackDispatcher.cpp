/**
 * ============================================================================
 * 2011/08/01
 * $Id: CallbackDispatcher.cpp 190 2012-01-30 18:34:54Z whirlwind $ Juno
 * ============================================================================
 */

#include "aquila/ddesvr/CallbackDispatcher.h"

namespace aquila {
	namespace ddesvr {

CallbackDispatcher::CallbackDispatcher(IServiceMap* pServiceMap, IEvent* pEvent)
  : serviceMap(pServiceMap), e(pEvent)
{
}

CallbackDispatcher::~CallbackDispatcher() {
}

bool CallbackDispatcher::onConnect(IString* topic, IString* service,
								   PCONVCONTEXT pContext, bool isSameInstance)
{
	string serviceName = service->getString();
	if ( serviceMap->has(serviceName) ) {
		return serviceMap->get(serviceName)
			->onConnect(topic, service, pContext, isSameInstance);
	}
	printf("CallbackDispatcher::onConnect: ignore unknown service: %s\n",
		serviceName.c_str());
	return false;
}

void CallbackDispatcher::onConnectConfirm(IConversation* conv, IString* topic,
										  IString* service, bool isSameInstance)
{
	string serviceName = service->getString();
	if ( serviceMap->has(serviceName) ) {
		serviceMap->get(serviceName)
			->onConnectConfirm(conv, topic, service, isSameInstance);
	} else {
		printf("CallbackDispatcher::onConnectConfirm: ignore unknown service: %s\n",
			serviceName.c_str());
	}
}

void CallbackDispatcher::onDisconnect(IConversation* conv,
									  bool isSameInstance)
{
	string serviceName = conv->getServiceName();
	if ( serviceMap->has(serviceName) ) {
		serviceMap->get(serviceName)->onDisconnect(conv, isSameInstance);
	} else {
		printf("CallbackDispatcher::onDisconnect: ignore unknown service: %s\n",
			serviceName.c_str());
	}
}

int CallbackDispatcher::onPoke(UINT uFmt, IConversation* conv, IString* topic,
							   IString* item, IData* data)
{
	string serviceName = conv->getServiceName();
	if ( serviceMap->has(serviceName) ) {
		return serviceMap->get(serviceName)
			->onPoke(uFmt, conv, topic, item, data);
	}
	printf("CallbackDispatcher::onPoke: ignore unknown service: %s\n",
		serviceName.c_str());
	return DDE_FACK;
}

void CallbackDispatcher::onRegister(IString* service, IString* instanceName) {
	string serviceName = service->getString();
	if ( serviceMap->has(serviceName) ) {
		serviceMap->get(serviceName)->onRegister(service, instanceName);
		e->set();
	} else {
		printf("CallbackDispatcher::onRegister: ignore unknown service: %s\n",
			serviceName.c_str());
	}
}

void CallbackDispatcher::onUnregister(IString* service, IString* instanceName)
{
	string serviceName = service->getString();
	if ( serviceMap->has(serviceName) ) {
		serviceMap->get(serviceName)->onUnregister(service, instanceName);
		serviceMap->remove(serviceName);
		e->set();
	} else {
		printf("CallbackDispatcher::onUnregister: ignore unknown service: %s\n",
			serviceName.c_str());
	}
}

IServiceMap* CallbackDispatcher::getServiceMap() {
	return serviceMap;
}

IEvent* CallbackDispatcher::getEvent() {
	return e;
}

	} // end namespace ddesvr
} // end aquila