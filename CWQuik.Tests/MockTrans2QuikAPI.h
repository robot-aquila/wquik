#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "wquik/ITrans2QuikAPI.h"

class MockTrans2QuikAPI : public wquik::ITrans2QuikAPI {
public:
	virtual ~MockTrans2QuikAPI(void){};
	MOCK_METHOD9(SEND_SYNC_TRANSACTION, long(LPSTR lpstTransactionString,
		long* pnReplyCode, PDWORD pdwTransId, double* pdOrderNum,
		LPSTR lpstrResultMessage, DWORD dwResultMessageSize,
		long* pnExtendedErrorCode, LPSTR lpstErrorMessage,
		DWORD dwErrorMessageSize));
	MOCK_METHOD4(SEND_ASYNC_TRANSACTION, long(LPSTR lpstTransactionString,
		long* pnExtendedErrorCode, LPSTR lpstErrorMessage,
		DWORD dwErrorMessageSize));
	MOCK_METHOD4(CONNECT, long(LPSTR lpstConnectionParamsString,
		long* pnExtendedErrorCode, LPSTR lpstrErrorMessage,
		DWORD dwErrorMessageSize));
	MOCK_METHOD3(DISCONNECT, long(long* pnExtendedErrorCode,
		LPSTR lpstrErrorMessage, DWORD dwErrorMessageSize));
	MOCK_METHOD4(SET_CONNECTION_STATUS_CALLBACK, long(
		TRANS2QUIK_CONNECTION_STATUS_CALLBACK pfConnectionStatusCallback,
		long* pnExtendedErrorCode, LPSTR lpstrErrorMessage,
		DWORD dwErrorMessageSize));
	MOCK_METHOD4(SET_TRANSACTIONS_REPLY_CALLBACK, long(
		TRANS2QUIK_TRANSACTION_REPLY_CALLBACK pfTransactionReplyCallback,
		long* pnExtendedErrorCode, LPSTR lpstrErrorMessage,
		DWORD dwErrorMessageSize));
	MOCK_METHOD3(IS_QUIK_CONNECTED, long(long* pnExtendedErrorCode,
		LPSTR lpstrErrorMessage, DWORD dwErrorMessageSize));
	MOCK_METHOD3(IS_DLL_CONNECTED, long(long* pnExtendedErrorCode,
		LPSTR lpstrErrorMessage, DWORD dwErrorMessageSize));
	MOCK_METHOD2(SUBSCRIBE_ORDERS, long(LPSTR ClassCode, LPSTR Seccodes));
	MOCK_METHOD0(UNSUBSCRIBE_ORDERS, long());
	MOCK_METHOD1(START_ORDERS,
		long(TRANS2QUIK_ORDER_STATUS_CALLBACK pfnOrderStatusCallback));
	MOCK_METHOD1(ORDER_QTY, long(long nOrderDescriptor));
	MOCK_METHOD1(ORDER_DATE,long(long nOrderDescriptor));
	MOCK_METHOD1(ORDER_TIME, long(long nOrderDescriptor));
	MOCK_METHOD1(ORDER_ACTIVATION_TIME, long(long nOrderDescriptor));
	MOCK_METHOD1(ORDER_WITHDRAW_TIME, long(long nOrderDescriptor));
	MOCK_METHOD1(ORDER_EXPIRY, long(long nOrderDescriptor));
	MOCK_METHOD1(ORDER_ACCRUED_INT, double(long nOrderDescriptor));
	MOCK_METHOD1(ORDER_YIELD, double(long nOrderDescriptor));
	MOCK_METHOD1(ORDER_UID, long(long nOrderDescriptor));
	MOCK_METHOD1(ORDER_USERID, LPTSTR(long nOrderDescriptor));
	MOCK_METHOD1(ORDER_ACCOUNT, LPTSTR(long nOrderDescriptor));
	MOCK_METHOD1(ORDER_BROKERREF, LPTSTR(long nOrderDescriptor));
	MOCK_METHOD1(ORDER_CLIENT_CODE, LPTSTR(long nOrderDescriptor));
	MOCK_METHOD1(ORDER_FIRMID, LPTSTR(long nOrderDescriptor));
	MOCK_METHOD2(SUBSCRIBE_TRADES, long(LPSTR ClassCode, LPSTR Seccodes));
	MOCK_METHOD0(UNSUBSCRIBE_TRADES, long());
	MOCK_METHOD1(START_TRADES, long(
		TRANS2QUIK_TRADE_STATUS_CALLBACK pfnTradeStatusCallback));
	MOCK_METHOD1(TRADE_DATE, long(long nTradeDescriptor));
	MOCK_METHOD1(TRADE_SETTLE_DATE, long(long nTradeDescriptor));
	MOCK_METHOD1(TRADE_TIME, long(long nTradeDescriptor));
	MOCK_METHOD1(TRADE_IS_MARGINAL, long(long nTradeDescriptor));
	MOCK_METHOD1(TRADE_ACCRUED_INT, double(long nTradeDescriptor));
	MOCK_METHOD1(TRADE_YIELD, double(long nTradeDescriptor));
	MOCK_METHOD1(TRADE_TS_COMMISSION, double(long nTradeDescriptor));
	MOCK_METHOD1(TRADE_CLEARING_CENTER_COMMISSION, double(long nTradeDescriptor));
	MOCK_METHOD1(TRADE_EXCHANGE_COMMISSION, double(long nTradeDescriptor));
	MOCK_METHOD1(TRADE_TRADING_SYSTEM_COMMISSION, double(long nTradeDescriptor));
	MOCK_METHOD1(TRADE_PRICE2, double(long nTradeDescriptor));
	MOCK_METHOD1(TRADE_REPO_RATE, double(long nTradeDescriptor));
	MOCK_METHOD1(TRADE_REPO_VALUE, double(long nTradeDescriptor));
	MOCK_METHOD1(TRADE_REPO2_VALUE, double(long nTradeDescriptor));
	MOCK_METHOD1(TRADE_ACCRUED_INT2, double(long nTradeDescriptor));
	MOCK_METHOD1(TRADE_REPO_TERM, long(long nTradeDescriptor));
	MOCK_METHOD1(TRADE_START_DISCOUNT, double(long nTradeDescriptor));
	MOCK_METHOD1(TRADE_LOWER_DISCOUNT, double(long nTradeDescriptor));
	MOCK_METHOD1(TRADE_UPPER_DISCOUNT, double(long nTradeDescriptor));
	MOCK_METHOD1(TRADE_BLOCK_SECURITIES, long(long nTradeDescriptor));
	MOCK_METHOD1(TRADE_CURRENCY, LPTSTR(long nTradeDescriptor));
	MOCK_METHOD1(TRADE_SETTLE_CURRENCY, LPTSTR(long nTradeDescriptor));
	MOCK_METHOD1(TRADE_SETTLE_CODE, LPTSTR(long nTradeDescriptor));
	MOCK_METHOD1(TRADE_ACCOUNT, LPTSTR(long nTradeDescriptor));
	MOCK_METHOD1(TRADE_BROKERREF, LPTSTR(long nTradeDescriptor));
	MOCK_METHOD1(TRADE_CLIENT_CODE, LPTSTR(long nTradeDescriptor));
	MOCK_METHOD1(TRADE_USERID, LPTSTR(long nTradeDescriptor));
	MOCK_METHOD1(TRADE_FIRMID, LPTSTR(long nTradeDescriptor));
	MOCK_METHOD1(TRADE_PARTNER_FIRMID, LPTSTR(long nTradeDescriptor));
	MOCK_METHOD1(TRADE_EXCHANGE_CODE, LPTSTR(long nTradeDescriptor));
	MOCK_METHOD1(TRADE_STATION_ID, LPTSTR(long nTradeDescriptor));
};
