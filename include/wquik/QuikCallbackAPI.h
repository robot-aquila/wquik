#pragma once
#include "wquik/macros.h"
#include "wquik/IQuikCallbackAPI.h"
#include "aquila/core/IDll.h"

using namespace aquila::core;

namespace wquik {

#define FN_CONNECTION_STATUS_CALLBACK		"_ConnectionStatusCallback@12"
#define FN_ORDER_STATUS_CALLBACK			"_OrderStatusCallback@56"
#define FN_TRADE_STATUS_CALLBACK			"_TradeStatusCallback@56"
#define FN_TRANSACTION_REPLY_CALLBACK		"_TransactionReplyCallback@28"
#define FN_SET_HANDLER						"_setHandler@4"

typedef void FNPT(CONNECTION_STATUS_CALLBACK) (long nConnectionEvent, long nExtendedErrorCode, LPSTR lpstrInfoMessage);
typedef void FNPT(TRANSACTION_REPLY_CALLBACK) (long nTransactionResult, long nTransactionExtendedErrorCode, long nTransactionReplyCode, DWORD dwTransId, double dOrderNum, LPSTR lpstrTransactionReplyMessage);
typedef void FNPT(ORDER_STATUS_CALLBACK) (long nMode, DWORD dwTransID, double dNumber, LPSTR lpstrClassCode, LPSTR lpstrSecCode, double dPrice, long nBalance, double dValue, long nIsSell, long nStatus, long nOrderDescriptor);
typedef void FNPT(TRADE_STATUS_CALLBACK) (long nMode, double dNumber, double dOrderNum, LPSTR lpstrClassCode, LPSTR lpstrSecCode, double dPrice, long nQty, double dValue, long nIsSell, long nTradeDescriptor);
typedef void FNPT(SET_HANDLER) (IQuikCallbackHandler* handler);

class QuikCallbackAPI : public IQuikCallbackAPI
{
public:
	QuikCallbackAPI(IDll* pLib);
	virtual ~QuikCallbackAPI(void);
	virtual TRANS2QUIK_TRANSACTION_REPLY_CALLBACK getTransactionsReplyCallback();
	virtual TRANS2QUIK_CONNECTION_STATUS_CALLBACK getConnectionStatusCallback();
	virtual TRANS2QUIK_ORDER_STATUS_CALLBACK getOrderStatusCallback();
	virtual TRANS2QUIK_TRADE_STATUS_CALLBACK getTradeStatusCallback();
	virtual void setHandler(IQuikCallbackHandler* handler);
private:
	FNPAD(CONNECTION_STATUS_CALLBACK);
	FNPAD(ORDER_STATUS_CALLBACK);
	FNPAD(TRADE_STATUS_CALLBACK);
	FNPAD(TRANSACTION_REPLY_CALLBACK);
	FNPAD(SET_HANDLER);

	IDll* lib;
#ifdef CWQUIK_TESTING
#pragma message ("QuikCallbackAPI was generated with additional methods")
public:
	IDll* getLibrary() { return lib; }
#endif
};

} // end namespace wquik
