/**
 * ============================================================================
 * 2013-01-26
 * $Id: QTrans.cpp 576 2013-03-14 12:07:25Z whirlwind $
 * ============================================================================
 */

#include <iostream>
#include "aquila/qtrans/QTrans.h"
#include "aquila/core/SleshLibrary.h"

#pragma managed

namespace aquila {
	namespace qtrans {

QTrans::QTrans(QTransHandler* handler, std::string modulePath) {
	mHandler = gcnew QTransManagedHandler(handler);
	path = modulePath;
	bInit = false;
}

QTrans::~QTrans() {
	
}

void QTrans::init() {
	library = new core::SleshLibrary(path.c_str());
	FNPI(library, SEND_ASYNC_TRANSACTION);
	FNPI(library, CONNECT);
	FNPI(library, DISCONNECT);
	FNPI(library, SET_CONNECTION_STATUS_CALLBACK);
	FNPI(library, SET_TRANSACTIONS_REPLY_CALLBACK);
	FNPI(library, IS_QUIK_CONNECTED);
	FNPI(library, IS_DLL_CONNECTED);

	FNPI(library, SUBSCRIBE_ORDERS);
	FNPI(library, UNSUBSCRIBE_ORDERS);
	FNPI(library, START_ORDERS);

	FNPI(library, ORDER_ACCOUNT);
	FNPI(library, ORDER_CLIENT_CODE);
	FNPI(library, ORDER_FIRMID);
	FNPI(library, ORDER_QTY);
	FNPI(library, ORDER_DATE);
	FNPI(library, ORDER_TIME);
	FNPI(library, ORDER_ACTIVATION_TIME);
	FNPI(library, ORDER_WITHDRAW_TIME);
	FNPI(library, ORDER_EXPIRY);
	FNPI(library, ORDER_ACCRUED_INT);
	FNPI(library, ORDER_YIELD);
	FNPI(library, ORDER_UID);
	FNPI(library, ORDER_USERID);
	FNPI(library, ORDER_BROKERREF);

	FNPI(library, SUBSCRIBE_TRADES);
	FNPI(library, UNSUBSCRIBE_TRADES);
	FNPI(library, START_TRADES);

	FNPI(library, TRADE_DATE);
	FNPI(library, TRADE_SETTLE_DATE);
	FNPI(library, TRADE_TIME);
	FNPI(library, TRADE_IS_MARGINAL);
	FNPI(library, TRADE_ACCRUED_INT);
	FNPI(library, TRADE_YIELD);
	FNPI(library, TRADE_TS_COMMISSION);
	FNPI(library, TRADE_CLEARING_CENTER_COMMISSION);
	FNPI(library, TRADE_EXCHANGE_COMMISSION);
	FNPI(library, TRADE_TRADING_SYSTEM_COMMISSION);
	FNPI(library, TRADE_PRICE2);
	FNPI(library, TRADE_REPO_RATE);
	FNPI(library, TRADE_REPO_VALUE);
	FNPI(library, TRADE_REPO2_VALUE);
	FNPI(library, TRADE_ACCRUED_INT2);
	FNPI(library, TRADE_REPO_TERM);
	FNPI(library, TRADE_START_DISCOUNT);
	FNPI(library, TRADE_LOWER_DISCOUNT);
	FNPI(library, TRADE_UPPER_DISCOUNT);
	FNPI(library, TRADE_BLOCK_SECURITIES);

	FNPI(library, TRADE_CURRENCY);
	FNPI(library, TRADE_SETTLE_CURRENCY);
	FNPI(library, TRADE_SETTLE_CODE);
	FNPI(library, TRADE_ACCOUNT);
	FNPI(library, TRADE_BROKERREF);
	FNPI(library, TRADE_CLIENT_CODE);
	FNPI(library, TRADE_USERID);
	FNPI(library, TRADE_FIRMID);
	FNPI(library, TRADE_PARTNER_FIRMID);
	FNPI(library, TRADE_EXCHANGE_CODE);
	FNPI(library, TRADE_STATION_ID);


	long errCode = 0, result = 0;
	char errMsg[256];
	::memset(errMsg, 0, sizeof(errMsg));
	result = FNPA(SET_CONNECTION_STATUS_CALLBACK)
		(mHandler->getConnectionStatusFnPtr(), &errCode, errMsg,
		sizeof(errMsg));
	if ( result != TRANS2QUIK_SUCCESS ) {
		throw QTransException(errCode, errMsg);
	}
	result = FNPA(SET_TRANSACTIONS_REPLY_CALLBACK)
		(mHandler->getTransactionReplyFnPtr(), &errCode, errMsg,
		sizeof(errMsg));
	if ( result != TRANS2QUIK_SUCCESS ) {
		throw QTransException(errCode, errMsg);
	}
	bInit = true;
}

void QTrans::connect(string connParam) {
	if ( bInit == false ) {
		throw QTransException("Object not initialized");
	}
	string msg;
	long errCode = 0, result = 0;
	char errMsg[2048];
	::memset(errMsg, 0, sizeof(errMsg));
	result = FNPA(CONNECT)(connParam.c_str(), &errCode, errMsg,
		sizeof(errMsg));
	switch ( result ) {
		case TRANS2QUIK_SUCCESS:
			break;
		case TRANS2QUIK_QUIK_TERMINAL_NOT_FOUND:
			msg = "Terminal not found: ";
			msg.append(connParam);
			msg.append(" (");
			msg.append(errMsg);
			msg.append(")");
			throw QTransException(msg);
		case TRANS2QUIK_DLL_VERSION_NOT_SUPPORTED:
			msg = "Version not supported: ";
			msg.append(connParam);
			msg.append(" (");
			msg.append(errMsg);
			msg.append(")");
			throw QTransException(msg);
		case TRANS2QUIK_ALREADY_CONNECTED_TO_QUIK:
			throw QTransException("Already connected");
		case TRANS2QUIK_FAILED:
			throw QTransException(errCode, errMsg);
		default:
			string msg = "Unknown error: ";
			msg.append(errMsg);
			throw QTransException(errCode, msg.c_str());
	}
	
	result = FNPA(SUBSCRIBE_ORDERS)("", "");
	result = FNPA(SUBSCRIBE_TRADES)("", "");
	result = FNPA(START_ORDERS)(mHandler->getOrderStatusFnPtr());
	result = FNPA(START_TRADES)(mHandler->getTradeStatusFnPtr());
}

void QTrans::disconnect() {
	if ( bInit == false ) {
		throw QTransException("Object not initialized");
	}
	string msg;
	long errCode = 0, result = 0;
	char errMsg[256];
	::memset(errMsg, 0, sizeof(errMsg));

	FNPA(UNSUBSCRIBE_TRADES)();
	FNPA(UNSUBSCRIBE_ORDERS)();

	result = FNPA(DISCONNECT)(&errCode, errMsg, sizeof(errMsg));
	if ( result != TRANS2QUIK_SUCCESS ) {
		throw QTransException(errCode, errMsg);
	}
}

void QTrans::send(string transactionString) {
	if ( bInit == false ) {
		throw QTransException("Object not initialized");
	}
	string msg;
	long errCode = 0, result = 0;
	char errMsg[256];
	::memset(errMsg, 0, sizeof(errMsg));
	result = FNPA(SEND_ASYNC_TRANSACTION)(transactionString.c_str(),
		&errCode, errMsg, sizeof(errMsg));
	switch ( result ) {
		case TRANS2QUIK_SUCCESS:
			break;
		case TRANS2QUIK_WRONG_SYNTAX:
			msg = "Wrong syntax: ";
			msg.append(transactionString);
			throw QTransException(msg);
		case TRANS2QUIK_DLL_NOT_CONNECTED:
			throw QTransException("DLL not connected");
		case TRANS2QUIK_QUIK_NOT_CONNECTED:
			throw QTransException("QUIK not connected");
		case TRANS2QUIK_FAILED:
			throw QTransException(errCode, errMsg);
		default:
			string msg = "Unknown error: ";
			msg.append(errMsg);
			throw QTransException(errCode, msg.c_str());
	}
}

bool QTrans::isDllConnected() {
	long errCode = 0, result = 0;
	char errMsg[256];
	::memset(errMsg, 0, sizeof(errMsg));
	result = FNPA(IS_QUIK_CONNECTED)(&errCode, errMsg, sizeof(errMsg));
	return result == TRANS2QUIK_QUIK_CONNECTED;
}

bool QTrans::isQuikConnected() {
	long errCode = 0, result = 0;
	char errMsg[256];
	::memset(errMsg, 0, sizeof(errMsg));
	result = FNPA(IS_DLL_CONNECTED)(&errCode, errMsg, sizeof(errMsg));
	return result == TRANS2QUIK_DLL_CONNECTED;
}

std::string QTrans::getOrderAccount(unsigned long orderDescriptor) {
	const char* str = (const char*)FNPA(ORDER_ACCOUNT)(orderDescriptor);
	return str == 0 ? "" : str;
}

std::string QTrans::getOrderFirmId(unsigned long orderDescriptor) {
	const char* str = (const char*)FNPA(ORDER_FIRMID)(orderDescriptor);
	return str == 0 ? "" : str;
}

std::string QTrans::getOrderClientCode(unsigned long orderDescriptor) {
	const char* str = (const char*)FNPA(ORDER_CLIENT_CODE)(orderDescriptor);
	return str == 0 ? "" : str;
}

unsigned long QTrans::getOrderQty(unsigned long orderDescriptor) {
	return FNPA(ORDER_QTY)(orderDescriptor);
}

unsigned long QTrans::getOrderDate(unsigned long orderDescriptor) {
	return FNPA(ORDER_DATE)(orderDescriptor);
}

unsigned long QTrans::getOrderTime(unsigned long orderDescriptor) {
	return FNPA(ORDER_TIME)(orderDescriptor);
}

unsigned long QTrans::getOrderActivationTime(unsigned long orderDescriptor) {
	return FNPA(ORDER_ACTIVATION_TIME)(orderDescriptor);
}

unsigned long QTrans::getOrderWithdrawTime(unsigned long orderDescriptor) {
	return FNPA(ORDER_WITHDRAW_TIME)(orderDescriptor);
}

unsigned long QTrans::getOrderExpiry(unsigned long orderDescriptor) {
	return FNPA(ORDER_EXPIRY)(orderDescriptor);
}

double QTrans::getOrderAccruedInt(unsigned long orderDescriptor) {
	return FNPA(ORDER_ACCRUED_INT)(orderDescriptor);
}

double QTrans::getOrderYield(unsigned long orderDescriptor) {
	return FNPA(ORDER_YIELD)(orderDescriptor);
}

unsigned long QTrans::getOrderUid(unsigned long orderDescriptor) {
	return FNPA(ORDER_UID)(orderDescriptor);
}

std::string QTrans::getOrderUserId(unsigned long orderDescriptor) {
	const char* str = (const char*)FNPA(ORDER_USERID)(orderDescriptor);
	return str == 0 ? "" : str;
}

std::string QTrans::getOrderBrokerRef(unsigned long orderDescriptor) {
	const char* str = (const char*)FNPA(ORDER_BROKERREF)(orderDescriptor);
	return str == 0 ? "" : str;
}

unsigned long QTrans::getTradeDate(unsigned long tradeDescriptor) {
	return FNPA(TRADE_DATE)(tradeDescriptor);
}

unsigned long QTrans::getTradeSettleDate(unsigned long tradeDescriptor) {
	return FNPA(TRADE_SETTLE_DATE)(tradeDescriptor);
}

unsigned long QTrans::getTradeTime(unsigned long tradeDescriptor) {
	return FNPA(TRADE_TIME)(tradeDescriptor);
}

bool QTrans::getTradeIsMarginal(unsigned long tradeDescriptor) {
	return FNPA(TRADE_IS_MARGINAL)(tradeDescriptor) == 1;
}

double QTrans::getTradeAccruedInt(unsigned long tradeDescriptor) {
	return FNPA(TRADE_ACCRUED_INT)(tradeDescriptor);
}

double QTrans::getTradeYield(unsigned long tradeDescriptor) {
	return FNPA(TRADE_YIELD)(tradeDescriptor);
}

double QTrans::getTradeTsCommission(unsigned long tradeDescriptor) {
	return FNPA(TRADE_TS_COMMISSION)(tradeDescriptor);
}

double QTrans::getTradeClearingCenterCommission(unsigned long tradeDescriptor) {
	return FNPA(TRADE_CLEARING_CENTER_COMMISSION)(tradeDescriptor);
}

double QTrans::getTradeExchangeCommission(unsigned long tradeDescriptor) {
	return FNPA(TRADE_EXCHANGE_COMMISSION)(tradeDescriptor);
}

double QTrans::getTradeTradingSystemCommission(unsigned long tradeDescriptor) {
	return FNPA(TRADE_TRADING_SYSTEM_COMMISSION)(tradeDescriptor);
}

double QTrans::getTradePrice2(unsigned long tradeDescriptor) {
	return FNPA(TRADE_PRICE2)(tradeDescriptor);
}

double QTrans::getTradeRepoRate(unsigned long tradeDescriptor) {
	return FNPA(TRADE_REPO_RATE)(tradeDescriptor);
}

double QTrans::getTradeRepoValue(unsigned long tradeDescriptor) {
	return FNPA(TRADE_REPO_VALUE)(tradeDescriptor);
}

double QTrans::getTradeRepo2Value(unsigned long tradeDescriptor) {
	return FNPA(TRADE_REPO2_VALUE)(tradeDescriptor);
}

double QTrans::getTradeAccruedInt2(unsigned long tradeDescriptor) {
	return FNPA(TRADE_ACCRUED_INT2)(tradeDescriptor);
}

long QTrans::getTradeRepoTerm(unsigned long tradeDescriptor) {
	return FNPA(TRADE_REPO_TERM)(tradeDescriptor);
}

double QTrans::getTradeStartDiscount(unsigned long tradeDescriptor) {
	return FNPA(TRADE_START_DISCOUNT)(tradeDescriptor);
}

double QTrans::getTradeLowerDiscount(unsigned long tradeDescriptor) {
	return FNPA(TRADE_LOWER_DISCOUNT)(tradeDescriptor);
}

double QTrans::getTradeUpperDiscount(unsigned long tradeDescriptor) {
	return FNPA(TRADE_UPPER_DISCOUNT)(tradeDescriptor);
}

bool QTrans::getTradeBlockSecurities(unsigned long tradeDescriptor) {
	return FNPA(TRADE_BLOCK_SECURITIES)(tradeDescriptor) == 1;
}

std::string QTrans::getTradeCurrency(unsigned long tradeDescriptor) {
	const char* str = (const char*)FNPA(TRADE_CURRENCY)(tradeDescriptor);
	return str == 0 ? "" : str;
}

std::string QTrans::getTradeSettleCurrency(unsigned long tradeDescriptor) {
	const char* str = (const char*)FNPA(TRADE_SETTLE_CURRENCY)(tradeDescriptor);
	return str == 0 ? "" : str;
}

std::string QTrans::getTradeSettleCode(unsigned long tradeDescriptor) {
	const char* str = (const char*)FNPA(TRADE_SETTLE_CODE)(tradeDescriptor);
	return str == 0 ? "" : str;
}

std::string QTrans::getTradeAccount(unsigned long tradeDescriptor) {
	const char* str = (const char*)FNPA(TRADE_ACCOUNT)(tradeDescriptor);
	return str == 0 ? "" : str;
}

std::string QTrans::getTradeBrokerRef(unsigned long tradeDescriptor) {
	const char* str = (const char*)FNPA(TRADE_BROKERREF)(tradeDescriptor);
	return str == 0 ? "" : str;
}

std::string QTrans::getTradeClientCode(unsigned long tradeDescriptor) {
	const char* str = (const char*)FNPA(TRADE_CLIENT_CODE)(tradeDescriptor);
	return str == 0 ? "" : str;
}

std::string QTrans::getTradeUserId(unsigned long tradeDescriptor) {
	const char* str = (const char*)FNPA(TRADE_USERID)(tradeDescriptor);
	return str == 0 ? "" : str;
}

std::string QTrans::getTradeFirmId(unsigned long tradeDescriptor) {
	const char* str = (const char*)FNPA(TRADE_FIRMID)(tradeDescriptor);
	return str == 0 ? "" : str;
}

std::string QTrans::getTradePartnerFirmId(unsigned long tradeDescriptor) {
	const char* str = (const char*)FNPA(TRADE_PARTNER_FIRMID)(tradeDescriptor);
	return str == 0 ? "" : str;
}

std::string QTrans::getTradeExchangeCode(unsigned long tradeDescriptor) {
	const char* str = (const char*)FNPA(TRADE_EXCHANGE_CODE)(tradeDescriptor);
	return str == 0 ? "" : str;
}

std::string QTrans::getTradeStationId(unsigned long tradeDescriptor) {
	const char* str = (const char*)FNPA(TRADE_STATION_ID)(tradeDescriptor);
	return str == 0 ? "" : str;
}

	} // end namespace qtrans
} // end namespace aquila

