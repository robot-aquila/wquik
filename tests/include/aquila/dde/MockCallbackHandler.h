/**
 * ============================================================================
 * 2011/07/18
 * $Id: MockCallbackHandler.h 96 2011-08-11 17:36:58Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/dde/ICallbackHandler.h"

namespace aquila {
	namespace dde {

class MockCallbackHandler : public ICallbackHandler {
public:
	virtual ~MockCallbackHandler() { }

	MOCK_METHOD4(onConnect, bool(IString* topic, IString* service,
		PCONVCONTEXT pContext, bool isSameInstance));
	MOCK_METHOD4(onConnectConfirm, void(IConversation* conv, IString* topic,
		IString* service, bool isSameInstance));
	MOCK_METHOD2(onDisconnect, void(IConversation* conv, bool isSameInstance));
	MOCK_METHOD5(onPoke, int(UINT uFmt, IConversation* conv, IString* topic,
		IString* item, IData* data));
	MOCK_METHOD2(onRegister, void(IString* baseName, IString* instanceName));
	MOCK_METHOD2(onUnregister, void(IString* baseName, IString* instanceName));

};

	} // end namespace dde
} // end namespace aquila