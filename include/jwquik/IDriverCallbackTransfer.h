#pragma once
#include <jni.h>
#include <jwquik/JWQuik.h>
#include <wquik/ITransactionDriver.h>
#include <aquila/core/IReferenceCounted.h>
#include <jwquik/JavaWrapper.h>

using namespace wquik;
using namespace aquila::core;

namespace jwquik {

class IDriverCallbackTransfer :
	public IReferenceCounted,
	public ITransactionDriverCallback
{
public:
	virtual ~IDriverCallbackTransfer(void){};
	virtual ITransactionDriver* getDriver()=0;
	virtual void onConnectionStatus(long eventId, long errorCode,
		const char* message)=0;
	virtual void onTransactionReply(long result, long errorCode,
		const TransactionResult* tr)=0;
	virtual void onOrderStatus(long mode, IOrder* order)=0;
	virtual void onTradeStatus(long mode, ITrade* trade)=0;
};

} // end namespace jwquik
