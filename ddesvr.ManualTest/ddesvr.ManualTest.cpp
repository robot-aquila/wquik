// ddesvr.ManualTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "aquila/core/auto_drop.h"
#include "aquila/core/WinApi.h"
#include "aquila/dde/ICallbackHandler.h"
#include "aquila/ddesvr/Server.h"
#include <string>

using namespace std;
using namespace aquila;
using namespace aquila::core;
using namespace aquila::ddesvr;

class CallbackHandler : public ICallbackHandler {
public:

	CallbackHandler(string serviceName, IEvent* pEvent)
		: name(serviceName), e(pEvent)
	{

	}

	virtual ~CallbackHandler() {
	
	}

	bool onConnect(IString* topic, IString* service, PCONVCONTEXT pContext,
		bool isSameInstance)
	{
		printf("TID:%x, %s::onConnect: topic=%s, service=%s\n",
			::GetCurrentThreadId(),name.c_str(), 
			topic->getString().c_str(), service->getString().c_str());
		return true;
	}

	void onConnectConfirm(IConversation* conv, IString* topic,
		IString* service, bool isSameInstance)
	{
		printf("TID:%x, %s::onConnectConfirm: topic=%s, service=%s\n",
			::GetCurrentThreadId(),name.c_str(), 
			topic->getString().c_str(), service->getString().c_str());

	}

	void onDisconnect(IConversation* conv, bool isSameInstance) {
		printf("TID:%x, %s::onDisconnect: topic=%s\n",
			::GetCurrentThreadId(), name.c_str(), conv->getTopic().c_str());
		e->set();
	}

	int onPoke(UINT uFmt, IConversation* conv, IString* topic, IString* item,
		IData* data)
	{
		printf("TID:%x, %s::onPoke: topic=%s, item=%s\n",
			::GetCurrentThreadId(), name.c_str(),
			topic->getString().c_str(), item->getString().c_str());
		return DDE_FACK;
	}

	void onRegister(IString* serviceName, IString* instanceName) {
		printf("TID:%x, %s::onRegister: service name=%s, instance name=%s\n",
			::GetCurrentThreadId(), name.c_str(),
			serviceName == NULL ? "NULL" : serviceName->getString().c_str(),
			instanceName == NULL ? "NULL" : instanceName->getString().c_str());
	}

	void onUnregister(IString* serviceName, IString* instanceName) {
		printf("TID:%x, %s::onUnregister: service name=%s, instance name=%s\n",
			::GetCurrentThreadId(), name.c_str(),
			serviceName == NULL ? "NULL" : serviceName->getString().c_str(),
			instanceName == NULL ? "NULL" : instanceName->getString().c_str());
	}

private:
	string name;
	auto_grab<IEvent> e;

};

int _tmain(int argc, _TCHAR* argv[]) {
	try {
		auto_drop<IWinApi> winApi(WinApi::getInstance());
		auto_drop<IEvent> e(winApi->createEvent(NULL, TRUE, FALSE, NULL));
		auto_drop<IServer> server(Server::getInstance());
		auto_drop<CallbackHandler> handler1(new CallbackHandler("AQUILA", e));
		auto_drop<CallbackHandler> handler2(new CallbackHandler("FOO", e));
		server->start();
		server->registerService("AQUILA", handler1);
		server->registerService("FOO", handler2);
		//::Sleep(1000);
		e->wait();
		server->unregisterService("FOO");
		server->unregisterService("TEST");
		server->stop();
		server->join();
		printf("exit\n");
	} catch ( std::exception& e ) {
		printf("Unhandled exception: %s\n", e.what());
		return 3;
	}
	return 0;
}
