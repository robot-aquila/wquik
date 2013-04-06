/**
 * ============================================================================
 * 2013-01-26
 * $Id: QTrans.h 576 2013-03-14 12:07:25Z whirlwind $
 * ============================================================================
 */

#pragma once
#include <string>
#include <vcclr.h>
#include "aquila/core/auto_drop.h"
#include "aquila/core/IDll.h"
#include "aquila/qtrans/trans2quik_api.h"
#include "aquila/qtrans/QTransHandler.h"
#include "aquila/qtrans/QTransException.h"
#include "aquila/qtrans/QTransManagedHandler.h"
#pragma warning(disable:4290)

using namespace std;

namespace aquila {
	namespace qtrans {

#define FN(fn) FN_ ## fn				// function name
#define FNP(fn) FNT_ ## fn				// function pointer
#define FNPT(fn) (__stdcall *FNP(fn))	// function pointer typedef
#define FNPA(fn) fptr_ ## fn			// function pointer attribute
#define FNPAD(fn) FNP(fn) FNPA(fn)		// function pointer attribute declaration
#define FNPI(lib, fn) FNPA(fn) = (FNP(fn))lib->getProcAddress(FN(fn))

/**
 * Имена необходимых функций в библиотеке TRANS2QUIK.dll
 */
#define FN_CONNECT							"_TRANS2QUIK_CONNECT@16"
#define FN_DISCONNECT						"_TRANS2QUIK_DISCONNECT@12"
#define FN_IS_DLL_CONNECTED					"_TRANS2QUIK_IS_DLL_CONNECTED@12"
#define FN_IS_QUIK_CONNECTED				"_TRANS2QUIK_IS_QUIK_CONNECTED@12"
#define FN_ORDER_ACCOUNT					"_TRANS2QUIK_ORDER_ACCOUNT@4"
#define FN_ORDER_ACCRUED_INT				"_TRANS2QUIK_ORDER_ACCRUED_INT@4"
#define FN_ORDER_ACTIVATION_TIME			"_TRANS2QUIK_ORDER_ACTIVATION_TIME@4"
#define FN_ORDER_BROKERREF					"_TRANS2QUIK_ORDER_BROKERREF@4"
#define FN_ORDER_CLIENT_CODE				"_TRANS2QUIK_ORDER_CLIENT_CODE@4"
#define FN_ORDER_DATE						"_TRANS2QUIK_ORDER_DATE@4"
#define FN_ORDER_EXPIRY						"_TRANS2QUIK_ORDER_EXPIRY@4"
#define FN_ORDER_FIRMID						"_TRANS2QUIK_ORDER_FIRMID@4"
#define FN_ORDER_QTY						"_TRANS2QUIK_ORDER_QTY@4"
#define FN_ORDER_TIME						"_TRANS2QUIK_ORDER_TIME@4"
#define FN_ORDER_UID						"_TRANS2QUIK_ORDER_UID@4"
#define FN_ORDER_USERID						"_TRANS2QUIK_ORDER_USERID@4"
#define FN_ORDER_WITHDRAW_TIME				"_TRANS2QUIK_ORDER_WITHDRAW_TIME@4"
#define FN_ORDER_YIELD						"_TRANS2QUIK_ORDER_YIELD@4"
#define FN_SEND_ASYNC_TRANSACTION			"_TRANS2QUIK_SEND_ASYNC_TRANSACTION@16"
#define FN_SEND_SYNC_TRANSACTION			"_TRANS2QUIK_SEND_SYNC_TRANSACTION@36"
#define FN_SET_CONNECTION_STATUS_CALLBACK	"_TRANS2QUIK_SET_CONNECTION_STATUS_CALLBACK@16"
#define FN_SET_TRANSACTIONS_REPLY_CALLBACK	"_TRANS2QUIK_SET_TRANSACTIONS_REPLY_CALLBACK@16"
#define FN_START_ORDERS						"_TRANS2QUIK_START_ORDERS@4"
#define FN_START_TRADES						"_TRANS2QUIK_START_TRADES@4"
#define FN_SUBSCRIBE_ORDERS					"_TRANS2QUIK_SUBSCRIBE_ORDERS@8"
#define FN_SUBSCRIBE_TRADES					"_TRANS2QUIK_SUBSCRIBE_TRADES@8"
#define FN_TRADE_ACCOUNT					"_TRANS2QUIK_TRADE_ACCOUNT@4"
#define FN_TRADE_ACCRUED_INT2				"_TRANS2QUIK_TRADE_ACCRUED_INT2@4"
#define FN_TRADE_ACCRUED_INT				"_TRANS2QUIK_TRADE_ACCRUED_INT@4"
#define FN_TRADE_BLOCK_SECURITIES			"_TRANS2QUIK_TRADE_BLOCK_SECURITIES@4"
#define FN_TRADE_BROKERREF					"_TRANS2QUIK_TRADE_BROKERREF@4"
#define FN_TRADE_CLEARING_CENTER_COMMISSION	"_TRANS2QUIK_TRADE_CLEARING_CENTER_COMMISSION@4"
#define FN_TRADE_CLIENT_CODE				"_TRANS2QUIK_TRADE_CLIENT_CODE@4"
#define FN_TRADE_CURRENCY					"_TRANS2QUIK_TRADE_CURRENCY@4"
#define FN_TRADE_DATE						"_TRANS2QUIK_TRADE_DATE@4"
#define FN_TRADE_EXCHANGE_CODE				"_TRANS2QUIK_TRADE_EXCHANGE_CODE@4"
#define FN_TRADE_EXCHANGE_COMMISSION		"_TRANS2QUIK_TRADE_EXCHANGE_COMMISSION@4"
#define FN_TRADE_FIRMID						"_TRANS2QUIK_TRADE_FIRMID@4"
#define FN_TRADE_IS_MARGINAL				"_TRANS2QUIK_TRADE_IS_MARGINAL@4"
#define FN_TRADE_LOWER_DISCOUNT				"_TRANS2QUIK_TRADE_LOWER_DISCOUNT@4"
#define FN_TRADE_PARTNER_FIRMID				"_TRANS2QUIK_TRADE_PARTNER_FIRMID@4"
#define FN_TRADE_PRICE2						"_TRANS2QUIK_TRADE_PRICE2@4"
#define FN_TRADE_REPO2_VALUE				"_TRANS2QUIK_TRADE_REPO2_VALUE@4"
#define FN_TRADE_REPO_RATE					"_TRANS2QUIK_TRADE_REPO_RATE@4"
#define FN_TRADE_REPO_TERM					"_TRANS2QUIK_TRADE_REPO_TERM@4"
#define FN_TRADE_REPO_VALUE					"_TRANS2QUIK_TRADE_REPO_VALUE@4"
#define FN_TRADE_SETTLE_CODE				"_TRANS2QUIK_TRADE_SETTLE_CODE@4"
#define FN_TRADE_SETTLE_CURRENCY			"_TRANS2QUIK_TRADE_SETTLE_CURRENCY@4"
#define FN_TRADE_SETTLE_DATE				"_TRANS2QUIK_TRADE_SETTLE_DATE@4"
#define FN_TRADE_START_DISCOUNT				"_TRANS2QUIK_TRADE_START_DISCOUNT@4"
#define FN_TRADE_STATION_ID					"_TRANS2QUIK_TRADE_STATION_ID@4"
#define FN_TRADE_TIME						"_TRANS2QUIK_TRADE_TIME@4"
#define FN_TRADE_TRADING_SYSTEM_COMMISSION	"_TRANS2QUIK_TRADE_TRADING_SYSTEM_COMMISSION@4"
#define FN_TRADE_TS_COMMISSION				"_TRANS2QUIK_TRADE_TS_COMMISSION@4"
#define FN_TRADE_UPPER_DISCOUNT				"_TRANS2QUIK_TRADE_UPPER_DISCOUNT@4"
#define FN_TRADE_USERID						"_TRANS2QUIK_TRADE_USERID@4"
#define FN_TRADE_YIELD						"_TRANS2QUIK_TRADE_YIELD@4"
#define FN_UNSUBSCRIBE_ORDERS				"_TRANS2QUIK_UNSUBSCRIBE_ORDERS@0"
#define FN_UNSUBSCRIBE_TRADES				"_TRANS2QUIK_UNSUBSCRIBE_TRADES@0"


typedef long FNPT(SEND_SYNC_TRANSACTION) (LPCSTR lpstTransactionString, long* pnReplyCode, PDWORD pdwTransId, double* pdOrderNum, LPSTR lpstrResultMessage, DWORD dwResultMessageSize, long* pnExtendedErrorCode, LPSTR lpstErrorMessage, DWORD dwErrorMessageSize);
typedef long FNPT(SEND_ASYNC_TRANSACTION) (LPCSTR lpstTransactionString, long* pnExtendedErrorCode, LPSTR lpstErrorMessage, DWORD dwErrorMessageSize);
typedef long FNPT(CONNECT) (LPCSTR lpstConnectionParamsString, long* pnExtendedErrorCode, LPSTR lpstrErrorMessage, DWORD dwErrorMessageSize);
typedef long FNPT(DISCONNECT) (long* pnExtendedErrorCode, LPSTR lpstrErrorMessage, DWORD dwErrorMessageSize);
typedef long FNPT(SET_CONNECTION_STATUS_CALLBACK) (TRANS2QUIK_CONNECTION_STATUS_CALLBACK pfConnectionStatusCallback, long* pnExtendedErrorCode, LPSTR lpstrErrorMessage, DWORD dwErrorMessageSize);
typedef long FNPT(SET_TRANSACTIONS_REPLY_CALLBACK) (TRANS2QUIK_TRANSACTION_REPLY_CALLBACK pfTransactionReplyCallback, long* pnExtendedErrorCode, LPSTR lpstrErrorMessage, DWORD dwErrorMessageSize);
typedef long FNPT(IS_QUIK_CONNECTED) (long* pnExtendedErrorCode, LPSTR lpstrErrorMessage, DWORD dwErrorMessageSize);
typedef long FNPT(IS_DLL_CONNECTED) (long* pnExtendedErrorCode, LPSTR lpstrErrorMessage, DWORD dwErrorMessageSize);

typedef long FNPT(SUBSCRIBE_ORDERS) (LPSTR ClassCode, LPSTR Seccodes);
typedef long FNPT(UNSUBSCRIBE_ORDERS) ();
typedef long FNPT(START_ORDERS) (TRANS2QUIK_ORDER_STATUS_CALLBACK pfnOrderStatusCallback);

typedef long FNPT(ORDER_QTY) (long nOrderDescriptor);
typedef long FNPT(ORDER_DATE) (long nOrderDescriptor);
typedef long FNPT(ORDER_TIME) (long nOrderDescriptor);
typedef long FNPT(ORDER_ACTIVATION_TIME) (long nOrderDescriptor);
typedef long FNPT(ORDER_WITHDRAW_TIME) (long nOrderDescriptor);
typedef long FNPT(ORDER_EXPIRY) (long nOrderDescriptor);
typedef double FNPT(ORDER_ACCRUED_INT) (long nOrderDescriptor);
typedef double FNPT(ORDER_YIELD) (long nOrderDescriptor);
typedef long FNPT(ORDER_UID) (long nOrderDescriptor);

typedef LPTSTR FNPT(ORDER_USERID) (long nOrderDescriptor);
typedef LPTSTR FNPT(ORDER_ACCOUNT) (long nOrderDescriptor); 
typedef LPTSTR FNPT(ORDER_BROKERREF) (long nOrderDescriptor); 
typedef LPTSTR FNPT(ORDER_CLIENT_CODE) (long nOrderDescriptor); 
typedef LPTSTR FNPT(ORDER_FIRMID) (long nOrderDescriptor); 

typedef long FNPT(SUBSCRIBE_TRADES) (LPSTR ClassCode, LPSTR Seccodes);
typedef long FNPT(UNSUBSCRIBE_TRADES) ();
typedef long FNPT(START_TRADES)(TRANS2QUIK_TRADE_STATUS_CALLBACK pfnTradeStatusCallback);

typedef long FNPT(TRADE_DATE) (long nTradeDescriptor);
typedef long FNPT(TRADE_SETTLE_DATE) (long nTradeDescriptor);
typedef long FNPT(TRADE_TIME) (long nTradeDescriptor);
typedef long FNPT(TRADE_IS_MARGINAL) (long nTradeDescriptor);
typedef double FNPT(TRADE_ACCRUED_INT) (long nTradeDescriptor);
typedef double FNPT(TRADE_YIELD) (long nTradeDescriptor);
typedef double FNPT(TRADE_TS_COMMISSION) (long nTradeDescriptor);
typedef double FNPT(TRADE_CLEARING_CENTER_COMMISSION) (long nTradeDescriptor);
typedef double FNPT(TRADE_EXCHANGE_COMMISSION) (long nTradeDescriptor);
typedef double FNPT(TRADE_TRADING_SYSTEM_COMMISSION) (long nTradeDescriptor);
typedef double FNPT(TRADE_PRICE2) (long nTradeDescriptor);
typedef double FNPT(TRADE_REPO_RATE) (long nTradeDescriptor);
typedef double FNPT(TRADE_REPO_VALUE) (long nTradeDescriptor);
typedef double FNPT(TRADE_REPO2_VALUE) (long nTradeDescriptor);
typedef double FNPT(TRADE_ACCRUED_INT2) (long nTradeDescriptor);
typedef long FNPT(TRADE_REPO_TERM) (long nTradeDescriptor);
typedef double FNPT(TRADE_START_DISCOUNT) (long nTradeDescriptor);
typedef double FNPT(TRADE_LOWER_DISCOUNT) (long nTradeDescriptor);
typedef double FNPT(TRADE_UPPER_DISCOUNT) (long nTradeDescriptor);
typedef long FNPT(TRADE_BLOCK_SECURITIES) (long nTradeDescriptor);

typedef LPTSTR FNPT(TRADE_CURRENCY) (long nTradeDescriptor);
typedef LPTSTR FNPT(TRADE_SETTLE_CURRENCY) (long nTradeDescriptor);
typedef LPTSTR FNPT(TRADE_SETTLE_CODE) (long nTradeDescriptor);
typedef LPTSTR FNPT(TRADE_ACCOUNT) (long nTradeDescriptor);
typedef LPTSTR FNPT(TRADE_BROKERREF) (long nTradeDescriptor);
typedef LPTSTR FNPT(TRADE_CLIENT_CODE) (long nTradeDescriptor);
typedef LPTSTR FNPT(TRADE_USERID) (long nTradeDescriptor);
typedef LPTSTR FNPT(TRADE_FIRMID) (long nTradeDescriptor);
typedef LPTSTR FNPT(TRADE_PARTNER_FIRMID) (long nTradeDescriptor);
typedef LPTSTR FNPT(TRADE_EXCHANGE_CODE) (long nTradeDescriptor);
typedef LPTSTR FNPT(TRADE_STATION_ID) (long nTradeDescriptor);


class QTrans {
public:
	QTrans(QTransHandler* handler, std::string modulePath);
	virtual void init() throw (QTransException);
	virtual void connect(string connParam) throw (QTransException);
	virtual void disconnect() throw (QTransException);
	virtual void send(string transactionString) throw (QTransException);
	virtual bool isDllConnected();
	virtual bool isQuikConnected();
	virtual ~QTrans();

	virtual std::string getOrderAccount(unsigned long orderDescriptor);
	virtual std::string getOrderClientCode(unsigned long orderDescriptor);
	virtual std::string getOrderFirmId(unsigned long orderDescriptor);
	virtual unsigned long getOrderQty(unsigned long orderDescriptor);
	virtual unsigned long getOrderDate(unsigned long orderDescriptor);
	virtual unsigned long getOrderTime(unsigned long orderDescriptor);
	virtual unsigned long getOrderActivationTime(unsigned long orderDescriptor);
	virtual unsigned long getOrderWithdrawTime(unsigned long orderDescriptor);
	virtual unsigned long getOrderExpiry(unsigned long orderDescriptor);
	virtual double getOrderAccruedInt(unsigned long orderDescriptor);
	virtual double getOrderYield(unsigned long orderDescriptor);
	virtual unsigned long getOrderUid(unsigned long orderDescriptor);
	virtual std::string getOrderUserId(unsigned long orderDescriptor);
	virtual std::string getOrderBrokerRef(unsigned long orderDescriptor);

	virtual unsigned long getTradeDate(unsigned long tradeDescriptor);
	virtual unsigned long getTradeSettleDate(unsigned long tradeDescriptor);
	virtual unsigned long getTradeTime(unsigned long tradeDescriptor);
	virtual bool getTradeIsMarginal(unsigned long tradeDescriptor);
	virtual double getTradeAccruedInt(unsigned long tradeDescriptor);
	virtual double getTradeYield(unsigned long tradeDescriptor);
	virtual double getTradeTsCommission(unsigned long tradeDescriptor);
	virtual double getTradeClearingCenterCommission(unsigned long tradeDescriptor);
	virtual double getTradeExchangeCommission(unsigned long tradeDescriptor);
	virtual double getTradeTradingSystemCommission(unsigned long tradeDescriptor);
	virtual double getTradePrice2(unsigned long tradeDescriptor);
	virtual double getTradeRepoRate(unsigned long tradeDescriptor);
	virtual double getTradeRepoValue(unsigned long tradeDescriptor);
	virtual double getTradeRepo2Value(unsigned long tradeDescriptor);
	virtual double getTradeAccruedInt2(unsigned long tradeDescriptor);
	virtual long getTradeRepoTerm(unsigned long tradeDescriptor);
	virtual double getTradeStartDiscount(unsigned long tradeDescriptor);
	virtual double getTradeLowerDiscount(unsigned long tradeDescriptor);
	virtual double getTradeUpperDiscount(unsigned long tradeDescriptor);
	virtual bool getTradeBlockSecurities(unsigned long tradeDescriptor);
	virtual std::string getTradeCurrency(unsigned long tradeDescriptor);
	virtual std::string getTradeSettleCurrency(unsigned long tradeDescriptor);
	virtual std::string getTradeSettleCode(unsigned long tradeDescriptor);
	virtual std::string getTradeAccount(unsigned long tradeDescriptor);
	virtual std::string getTradeBrokerRef(unsigned long tradeDescriptor);
	virtual std::string getTradeClientCode(unsigned long tradeDescriptor);
	virtual std::string getTradeUserId(unsigned long tradeDescriptor);
	virtual std::string getTradeFirmId(unsigned long tradeDescriptor);
	virtual std::string getTradePartnerFirmId(unsigned long tradeDescriptor);
	virtual std::string getTradeExchangeCode(unsigned long tradeDescriptor);
	virtual std::string getTradeStationId(unsigned long tradeDescriptor);

private:
	std::string path;
	gcroot<QTransManagedHandler^> mHandler;
	core::auto_drop<core::IDll> library;
	bool bInit;

	FNPAD(SEND_ASYNC_TRANSACTION);
	FNPAD(CONNECT);
	FNPAD(DISCONNECT);
	FNPAD(SET_CONNECTION_STATUS_CALLBACK);
	FNPAD(SET_TRANSACTIONS_REPLY_CALLBACK);
	FNPAD(IS_QUIK_CONNECTED);
	FNPAD(IS_DLL_CONNECTED);

	FNPAD(SUBSCRIBE_ORDERS);
	FNPAD(UNSUBSCRIBE_ORDERS);
	FNPAD(START_ORDERS);

	FNPAD(ORDER_ACCOUNT);
	FNPAD(ORDER_CLIENT_CODE);
	FNPAD(ORDER_FIRMID);
	
	FNPAD(ORDER_QTY);
	FNPAD(ORDER_DATE);
	FNPAD(ORDER_TIME);
	FNPAD(ORDER_ACTIVATION_TIME);
	FNPAD(ORDER_WITHDRAW_TIME);
	FNPAD(ORDER_EXPIRY);
	FNPAD(ORDER_ACCRUED_INT);
	FNPAD(ORDER_YIELD);
	FNPAD(ORDER_UID);
	FNPAD(ORDER_USERID);
	FNPAD(ORDER_BROKERREF);

	FNPAD(SUBSCRIBE_TRADES);
	FNPAD(UNSUBSCRIBE_TRADES);
	FNPAD(START_TRADES);

	FNPAD(TRADE_DATE);
	FNPAD(TRADE_SETTLE_DATE);
	FNPAD(TRADE_TIME);
	FNPAD(TRADE_IS_MARGINAL);
	FNPAD(TRADE_ACCRUED_INT);
	FNPAD(TRADE_YIELD);
	FNPAD(TRADE_TS_COMMISSION);
	FNPAD(TRADE_CLEARING_CENTER_COMMISSION);
	FNPAD(TRADE_EXCHANGE_COMMISSION);
	FNPAD(TRADE_TRADING_SYSTEM_COMMISSION);
	FNPAD(TRADE_PRICE2);
	FNPAD(TRADE_REPO_RATE);
	FNPAD(TRADE_REPO_VALUE);
	FNPAD(TRADE_REPO2_VALUE);
	FNPAD(TRADE_ACCRUED_INT2);
	FNPAD(TRADE_REPO_TERM);
	FNPAD(TRADE_START_DISCOUNT);
	FNPAD(TRADE_LOWER_DISCOUNT);
	FNPAD(TRADE_UPPER_DISCOUNT);
	FNPAD(TRADE_BLOCK_SECURITIES);

	FNPAD(TRADE_CURRENCY);
	FNPAD(TRADE_SETTLE_CURRENCY);
	FNPAD(TRADE_SETTLE_CODE);
	FNPAD(TRADE_ACCOUNT);
	FNPAD(TRADE_BROKERREF);
	FNPAD(TRADE_CLIENT_CODE);
	FNPAD(TRADE_USERID);
	FNPAD(TRADE_FIRMID);
	FNPAD(TRADE_PARTNER_FIRMID);
	FNPAD(TRADE_EXCHANGE_CODE);
	FNPAD(TRADE_STATION_ID);

};

	} // end namespace qtrans
} // end namespace aquila