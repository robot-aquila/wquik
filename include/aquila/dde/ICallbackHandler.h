/**
 * ============================================================================
 * 2011/07/12
 * $Id: ICallbackHandler.h 101 2011-08-11 18:37:57Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#include <windows.h>
#include "aquila/core/IReferenceCounted.h"
#include "aquila/dde/IString.h"
#include "aquila/dde/IData.h"
#include "aquila/dde/IConversation.h"

using namespace aquila::core;

namespace aquila {
	namespace dde {

/**
  * Методы, которые нереализованы, так как незадействованы
  * в работе приемника данных от QUIK.

	 onExecute
	 onMonitor
	 onError
	 onWildConnect
	 onXactComplete
	 onRequest
	 onAdvStop
	 onAdvData
	 onAdvReq
	 onAdvStart
 */
class ICallbackHandler : public IReferenceCounted {
public:

	ICallbackHandler() { }

	virtual ~ICallbackHandler() { }

	virtual bool
		onConnect(IString* topic, IString* service, PCONVCONTEXT pContext,
			bool isSameInstance)=0;

	virtual void
		onConnectConfirm(IConversation* conv, IString* topic, IString* service,
			bool isSameInstance)=0;

	virtual void onDisconnect(IConversation* conv, bool isSameInstance)=0;

	/**
	 * @return DDE_FACK|DDE_FBUSY|DDE_FNOTPROCESSED
	 */
	virtual int
		onPoke(UINT uFmt, IConversation* conv, IString* topic, IString* item,
			IData* data)=0;

	virtual void
		onRegister(IString* service, IString* instanceName)=0;

	virtual void
		onUnregister(IString* service, IString* instanceName)=0;

};

	} // end namespace dde
} // end namespace aquila