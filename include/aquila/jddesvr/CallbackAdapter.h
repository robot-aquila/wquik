/**
 * ============================================================================
 * 2011/08/12
 * $Id: CallbackAdapter.h 543 2013-02-25 06:35:27Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#include "aquila/core/auto_drop.h"
#include "aquila/core/DataBuffer.h"
#include "aquila/dde/ICallbackHandler.h"
#include "aquila/jddesvr/ServiceHandler.h"
#include "aquila/xltable/Facade.h"

using namespace aquila::xltable;
using namespace aquila::core;

namespace aquila {
	namespace jddesvr {

class CallbackAdapter : public ICallbackHandler {
public:

	CallbackAdapter(ServiceHandler* serviceHandler)
	  : handler(serviceHandler),
		xlt(new Facade())
	{

	}

	virtual ~CallbackAdapter() {

	}

	bool onConnect(IString* topic, IString* service, PCONVCONTEXT pContext,
		bool isSameInstance)
	{
		return handler->onConnect(topic->getString()); 
	}

	void onConnectConfirm(IConversation* conv, IString* topic,
		IString* service, bool isSameInstance)
	{
		handler->onConnectConfirm(topic->getString());
	}

	void onDisconnect(IConversation* conv, bool isSameInstance) {
		handler->onDisconnect(conv->getTopic());
	}

	int onPoke(UINT uFmt, IConversation* conv, IString* topic,
		IString* item, IData* data)
	{
		auto_drop<DataBuffer> buffer(new DataBuffer(data->getSize()));
		data->getData(buffer->getPointer(), buffer->getSize(), 0);
		string str_topic = topic->getString();
		string str_item = item->getString();
		if ( false == handler->onRawData(str_topic.c_str(), str_item.c_str(),
			(char*)buffer->getPointer(), buffer->getSize()) )
		{
			auto_drop<IDataStream> stream(xlt->createStream(buffer));
			auto_drop<ITableRange> table(xlt->readTable(str_topic.c_str(),
				str_item.c_str(), stream));
			Table* pTable = new Table(table);
			handler->onData(pTable);
			delete pTable;
		}

		return DDE_FACK;
	}

	void onRegister(IString* service, IString* instanceName) {
		handler->onRegister();
	}

	void onUnregister(IString* service, IString* instanceName) {
		handler->onUnregister();
	}

private:
	ServiceHandler* handler;
	auto_drop<IFacade> xlt;
};

	} // end namespace jddesvr
} // end namespace aquila