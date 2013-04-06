/**
 * ============================================================================
 * 2011/07/18
 * $Id: Instance.cpp 101 2011-08-11 18:37:57Z whirlwind $ Juno
 * ============================================================================
 */

#include "aquila/dde/Instance.h"
#include "aquila/dde/String.h"
#include "aquila/dde/Data.h"
#include "aquila/dde/Conversation.h"
#include "aquila/core/auto_drop.h"

using namespace aquila::core;

namespace aquila {
	namespace dde {

static Instance* pInstance = NULL;

Instance::Instance(IWinApi* pWinApi, ICallbackHandler* pCallbackHandler,
				   int iCodePage)
	: winApi(pWinApi),
	  callbackHandler(pCallbackHandler),
	  codePage(iCodePage),
	  idInst(0)
{
	if ( NULL != pInstance ) {
		throw std::exception("Only one instance allowed");
	}
	if ( DMLERR_NO_ERROR !=
		winApi->DdeInitialize(&idInst, Instance::CallbackFunction, 0, 0) )
	{
		throw std::exception("initialize failed");
	}
	pInstance = this;
}

Instance::~Instance() {
	winApi->DdeUninitialize(idInst);
	pInstance = NULL;
}

HDDEDATA Instance::CallbackFunction(UINT uType, UINT uFmt, HCONV hconv,
	HSZ hsz1, HSZ hsz2, HDDEDATA hdata,
	ULONG_PTR dwData1, ULONG_PTR dwData2)
{
	auto_drop<IString> topic(pInstance->wrapString(hsz1));
	auto_drop<IString> item(pInstance->wrapString(hsz2));
	auto_drop<IData> data(pInstance->wrapData(hdata));
	auto_drop<IConversation> conv(pInstance->wrapConversation(hconv));
	bool result;

	switch ( uType ) {
	case XTYP_CONNECT:
		result = pInstance->callbackHandler->onConnect(topic, item,
			(PCONVCONTEXT)dwData1, dwData2 == 1 ? true : false);
		return (HDDEDATA)(result ? TRUE : FALSE);

	case XTYP_CONNECT_CONFIRM:
		pInstance->callbackHandler->onConnectConfirm(conv, topic, item,
			dwData2 == 1 ? true : false);
		return 0;

	case XTYP_DISCONNECT:
		pInstance->callbackHandler->onDisconnect(conv,
			dwData2 == 1 ? true : false);
		return 0;

	case XTYP_POKE:
		return (HDDEDATA)pInstance->callbackHandler->onPoke(uFmt, conv, topic,
			item, data);

	case XTYP_REGISTER:
		pInstance->callbackHandler->onRegister(topic, item);
		return 0;

	case XTYP_UNREGISTER:
		pInstance->callbackHandler->onUnregister(topic, item);
		return 0;

	}
	return 0;
}

ICallbackHandler* Instance::getCallbackHandler() {
	return callbackHandler;
}

IWinApi* Instance::getWinApi() {
	return winApi;
}

int Instance::getCodePage() {
	return codePage;
}

DWORD Instance::getId() {
	return idInst;
}

void Instance::nameService(IString* name, UINT afCmd) {
	winApi->DdeNameService(idInst, name->getHandle(), 0, afCmd);
}

int Instance::getLastError() {
	return winApi->DdeGetLastError(idInst);
}

IString* Instance::createString(std::string str) {
	return new String(this, winApi, str, codePage);
}

IString* Instance::wrapString(HSZ hsz) {
	if ( NULL == hsz ) {
		return NULL;
	}
	return new String(this, winApi, hsz, codePage);
}

IData* Instance::wrapData(HDDEDATA hData) {
	if ( NULL == hData ) {
		return NULL;
	}
	return new Data(this, winApi, hData);
}

IConversation* Instance::wrapConversation(HCONV hConv) {
	if ( NULL == hConv ) {
		return NULL;
	}
	return new Conversation(this, winApi, hConv);
}

	} // end namespace dde
} // end namespace aquila