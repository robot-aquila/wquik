#pragma once
#include <windows.h>
#include "wquik/trans2quik_api.h"
#include "wquik/IQuikCallbackHandler.h"
#include "aquila/core/IReferenceCounted.h"

using namespace aquila::core;

namespace wquik {

class IQuikCallbackAPI : public IReferenceCounted
{
public:
	virtual ~IQuikCallbackAPI(void){};
	virtual TRANS2QUIK_TRANSACTION_REPLY_CALLBACK getTransactionsReplyCallback()=0;
	virtual TRANS2QUIK_CONNECTION_STATUS_CALLBACK getConnectionStatusCallback()=0;
	virtual TRANS2QUIK_ORDER_STATUS_CALLBACK getOrderStatusCallback()=0;
	virtual TRANS2QUIK_TRADE_STATUS_CALLBACK getTradeStatusCallback()=0;
	virtual void setHandler(IQuikCallbackHandler* handler)=0;
};

} // end namespace wquik
