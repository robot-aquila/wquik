#pragma once
#include <windows.h>
#include "wquik/trans2quik_api.h"
#include "aquila/core/IReferenceCounted.h"

using namespace aquila::core;

namespace wquik {

class ITrans2QuikAPI : public IReferenceCounted
{
public:
	virtual ~ITrans2QuikAPI(void){};
	virtual long SEND_SYNC_TRANSACTION(LPSTR lpstTransactionString,
		long* pnReplyCode, PDWORD pdwTransId, double* pdOrderNum,
		LPSTR lpstrResultMessage, DWORD dwResultMessageSize,
		long* pnExtendedErrorCode, LPSTR lpstErrorMessage,
		DWORD dwErrorMessageSize)=0;
	virtual long SEND_ASYNC_TRANSACTION(LPSTR lpstTransactionString,
		long* pnExtendedErrorCode, LPSTR lpstErrorMessage,
		DWORD dwErrorMessageSize)=0;
	virtual long CONNECT(LPSTR lpstConnectionParamsString,
		long* pnExtendedErrorCode, LPSTR lpstrErrorMessage,
		DWORD dwErrorMessageSize)=0;
	virtual long DISCONNECT(long* pnExtendedErrorCode,
		LPSTR lpstrErrorMessage, DWORD dwErrorMessageSize)=0;
	virtual long SET_CONNECTION_STATUS_CALLBACK(
		TRANS2QUIK_CONNECTION_STATUS_CALLBACK pfConnectionStatusCallback,
		long* pnExtendedErrorCode, LPSTR lpstrErrorMessage,
		DWORD dwErrorMessageSize)=0;
	virtual long SET_TRANSACTIONS_REPLY_CALLBACK (
		TRANS2QUIK_TRANSACTION_REPLY_CALLBACK pfTransactionReplyCallback,
		long* pnExtendedErrorCode, LPSTR lpstrErrorMessage,
		DWORD dwErrorMessageSize)=0;
	virtual long IS_QUIK_CONNECTED(long* pnExtendedErrorCode,
		LPSTR lpstrErrorMessage, DWORD dwErrorMessageSize)=0;
	virtual long IS_DLL_CONNECTED(long* pnExtendedErrorCode,
		LPSTR lpstrErrorMessage, DWORD dwErrorMessageSize)=0;
	virtual long SUBSCRIBE_ORDERS(LPSTR ClassCode, LPSTR Seccodes)=0;
	virtual long UNSUBSCRIBE_ORDERS()=0;
	virtual long START_ORDERS(
		TRANS2QUIK_ORDER_STATUS_CALLBACK pfnOrderStatusCallback)=0;
	virtual long ORDER_QTY (long nOrderDescriptor)=0;
	virtual long ORDER_DATE(long nOrderDescriptor)=0;
	virtual long ORDER_TIME(long nOrderDescriptor)=0;
	virtual long ORDER_ACTIVATION_TIME(long nOrderDescriptor)=0;
	virtual long ORDER_WITHDRAW_TIME(long nOrderDescriptor)=0;
	virtual long ORDER_EXPIRY(long nOrderDescriptor)=0;
	virtual double ORDER_ACCRUED_INT(long nOrderDescriptor)=0;
	virtual double ORDER_YIELD(long nOrderDescriptor)=0;
	virtual long ORDER_UID(long nOrderDescriptor)=0;
	virtual LPTSTR ORDER_USERID(long nOrderDescriptor)=0;
	virtual LPTSTR ORDER_ACCOUNT(long nOrderDescriptor)=0;
	virtual LPTSTR ORDER_BROKERREF(long nOrderDescriptor)=0;
	virtual LPTSTR ORDER_CLIENT_CODE(long nOrderDescriptor)=0;
	virtual LPTSTR ORDER_FIRMID(long nOrderDescriptor)=0;
	virtual long SUBSCRIBE_TRADES(LPSTR ClassCode, LPSTR Seccodes)=0;
	virtual long UNSUBSCRIBE_TRADES()=0;
	virtual long START_TRADES(
		TRANS2QUIK_TRADE_STATUS_CALLBACK pfnTradeStatusCallback)=0;
	virtual long TRADE_DATE(long nTradeDescriptor)=0;
	virtual long TRADE_SETTLE_DATE(long nTradeDescriptor)=0;
	virtual long TRADE_TIME(long nTradeDescriptor)=0;
	virtual long TRADE_IS_MARGINAL(long nTradeDescriptor)=0;
	virtual double TRADE_ACCRUED_INT(long nTradeDescriptor)=0;
	virtual double TRADE_YIELD(long nTradeDescriptor)=0;
	virtual double TRADE_TS_COMMISSION(long nTradeDescriptor)=0;
	virtual double TRADE_CLEARING_CENTER_COMMISSION(long nTradeDescriptor)=0;
	virtual double TRADE_EXCHANGE_COMMISSION(long nTradeDescriptor)=0;
	virtual double TRADE_TRADING_SYSTEM_COMMISSION(long nTradeDescriptor)=0;
	virtual double TRADE_PRICE2(long nTradeDescriptor)=0;
	virtual double TRADE_REPO_RATE(long nTradeDescriptor)=0;
	virtual double TRADE_REPO_VALUE(long nTradeDescriptor)=0;
	virtual double TRADE_REPO2_VALUE(long nTradeDescriptor)=0;
	virtual double TRADE_ACCRUED_INT2(long nTradeDescriptor)=0;
	virtual long TRADE_REPO_TERM(long nTradeDescriptor)=0;
	virtual double TRADE_START_DISCOUNT(long nTradeDescriptor)=0;
	virtual double TRADE_LOWER_DISCOUNT(long nTradeDescriptor)=0;
	virtual double TRADE_UPPER_DISCOUNT(long nTradeDescriptor)=0;
	virtual long TRADE_BLOCK_SECURITIES(long nTradeDescriptor)=0;
	virtual LPTSTR TRADE_CURRENCY(long nTradeDescriptor)=0;
	virtual LPTSTR TRADE_SETTLE_CURRENCY(long nTradeDescriptor)=0;
	virtual LPTSTR TRADE_SETTLE_CODE(long nTradeDescriptor)=0;
	virtual LPTSTR TRADE_ACCOUNT(long nTradeDescriptor)=0;
	virtual LPTSTR TRADE_BROKERREF(long nTradeDescriptor)=0;
	virtual LPTSTR TRADE_CLIENT_CODE(long nTradeDescriptor)=0;
	virtual LPTSTR TRADE_USERID(long nTradeDescriptor)=0;
	virtual LPTSTR TRADE_FIRMID(long nTradeDescriptor)=0;
	virtual LPTSTR TRADE_PARTNER_FIRMID(long nTradeDescriptor)=0;
	virtual LPTSTR TRADE_EXCHANGE_CODE(long nTradeDescriptor)=0;
	virtual LPTSTR TRADE_STATION_ID(long nTradeDescriptor)=0;
};

} // end namespace wquik
