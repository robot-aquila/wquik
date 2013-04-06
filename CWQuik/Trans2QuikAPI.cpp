#include "wquik/Trans2QuikAPI.h"

namespace wquik {

Trans2QuikAPI::Trans2QuikAPI(IDll* pLib) {
	//try {
		FNPI(pLib, SEND_SYNC_TRANSACTION);
		FNPI(pLib, SEND_ASYNC_TRANSACTION);
		FNPI(pLib, CONNECT);
		FNPI(pLib, DISCONNECT);
		FNPI(pLib, SET_CONNECTION_STATUS_CALLBACK);
		FNPI(pLib, SET_TRANSACTIONS_REPLY_CALLBACK);
		FNPI(pLib, IS_QUIK_CONNECTED);
		FNPI(pLib, IS_DLL_CONNECTED);

		FNPI(pLib, SUBSCRIBE_ORDERS);
		FNPI(pLib, UNSUBSCRIBE_ORDERS);
		FNPI(pLib, START_ORDERS);

		FNPI(pLib, ORDER_QTY);
		FNPI(pLib, ORDER_DATE);
		FNPI(pLib, ORDER_TIME);
		FNPI(pLib, ORDER_ACTIVATION_TIME);
		FNPI(pLib, ORDER_WITHDRAW_TIME);
		FNPI(pLib, ORDER_EXPIRY);
		FNPI(pLib, ORDER_ACCRUED_INT);
		FNPI(pLib, ORDER_YIELD);
		FNPI(pLib, ORDER_UID);

		FNPI(pLib, ORDER_USERID);
		FNPI(pLib, ORDER_ACCOUNT); 
		FNPI(pLib, ORDER_BROKERREF); 
		FNPI(pLib, ORDER_CLIENT_CODE); 
		FNPI(pLib, ORDER_FIRMID); 

		FNPI(pLib, SUBSCRIBE_TRADES);
		FNPI(pLib, UNSUBSCRIBE_TRADES);
		FNPI(pLib, START_TRADES);

		FNPI(pLib, TRADE_DATE);
		FNPI(pLib, TRADE_SETTLE_DATE);
		FNPI(pLib, TRADE_TIME);
		FNPI(pLib, TRADE_IS_MARGINAL);
		FNPI(pLib, TRADE_ACCRUED_INT);
		FNPI(pLib, TRADE_YIELD);
		FNPI(pLib, TRADE_TS_COMMISSION);
		FNPI(pLib, TRADE_CLEARING_CENTER_COMMISSION);
		FNPI(pLib, TRADE_EXCHANGE_COMMISSION);
		FNPI(pLib, TRADE_TRADING_SYSTEM_COMMISSION);
		FNPI(pLib, TRADE_PRICE2);
		FNPI(pLib, TRADE_REPO_RATE);
		FNPI(pLib, TRADE_REPO_VALUE);
		FNPI(pLib, TRADE_REPO2_VALUE);
		FNPI(pLib, TRADE_ACCRUED_INT2);
		FNPI(pLib, TRADE_REPO_TERM);
		FNPI(pLib, TRADE_START_DISCOUNT);
		FNPI(pLib, TRADE_LOWER_DISCOUNT);
		FNPI(pLib, TRADE_UPPER_DISCOUNT);
		FNPI(pLib, TRADE_BLOCK_SECURITIES);

		FNPI(pLib, TRADE_CURRENCY);
		FNPI(pLib, TRADE_SETTLE_CURRENCY);
		FNPI(pLib, TRADE_SETTLE_CODE);
		FNPI(pLib, TRADE_ACCOUNT);
		FNPI(pLib, TRADE_BROKERREF);
		FNPI(pLib, TRADE_CLIENT_CODE);
		FNPI(pLib, TRADE_USERID);
		FNPI(pLib, TRADE_FIRMID);
		FNPI(pLib, TRADE_PARTNER_FIRMID);
		FNPI(pLib, TRADE_EXCHANGE_CODE);
		FNPI(pLib, TRADE_STATION_ID);

	//} catch ( LibraryException e ) {
		// TODO:
	//}
	lib = (IDll*)pLib->grab();
}

Trans2QuikAPI::~Trans2QuikAPI(void) {
	lib->drop();
}

long Trans2QuikAPI::SEND_SYNC_TRANSACTION(LPSTR lpstTransactionString,
		long* pnReplyCode, PDWORD pdwTransId, double* pdOrderNum,
		LPSTR lpstrResultMessage, DWORD dwResultMessageSize,
		long* pnExtendedErrorCode, LPSTR lpstErrorMessage,
		DWORD dwErrorMessageSize)
{
	return FNPA(SEND_SYNC_TRANSACTION)(lpstTransactionString,
		pnReplyCode, pdwTransId, pdOrderNum,
		lpstrResultMessage, dwResultMessageSize,
		pnExtendedErrorCode, lpstErrorMessage,
		dwErrorMessageSize);
}

long Trans2QuikAPI::SEND_ASYNC_TRANSACTION(LPSTR lpstTransactionString,
		long* pnExtendedErrorCode, LPSTR lpstErrorMessage,
		DWORD dwErrorMessageSize)
{
	return FNPA(SEND_ASYNC_TRANSACTION)(lpstTransactionString,
		pnExtendedErrorCode, lpstErrorMessage,
		dwErrorMessageSize);
}

long Trans2QuikAPI::CONNECT(LPSTR lpstConnectionParamsString,
		long* pnExtendedErrorCode, LPSTR lpstrErrorMessage,
		DWORD dwErrorMessageSize)
{
	return FNPA(CONNECT)(lpstConnectionParamsString,
		pnExtendedErrorCode, lpstrErrorMessage,
		dwErrorMessageSize);
}

long Trans2QuikAPI::DISCONNECT(long* pnExtendedErrorCode,
		LPSTR lpstrErrorMessage, DWORD dwErrorMessageSize)
{
	return FNPA(DISCONNECT)(pnExtendedErrorCode,
		lpstrErrorMessage, dwErrorMessageSize);
}

long Trans2QuikAPI::SET_CONNECTION_STATUS_CALLBACK(
		TRANS2QUIK_CONNECTION_STATUS_CALLBACK pfConnectionStatusCallback,
		long* pnExtendedErrorCode, LPSTR lpstrErrorMessage,
		DWORD dwErrorMessageSize)
{
	return FNPA(SET_CONNECTION_STATUS_CALLBACK)(
		pfConnectionStatusCallback,
		pnExtendedErrorCode, lpstrErrorMessage,
		dwErrorMessageSize);
}

long Trans2QuikAPI::SET_TRANSACTIONS_REPLY_CALLBACK (
		TRANS2QUIK_TRANSACTION_REPLY_CALLBACK pfTransactionReplyCallback,
		long* pnExtendedErrorCode, LPSTR lpstrErrorMessage,
		DWORD dwErrorMessageSize)
{
	return FNPA(SET_TRANSACTIONS_REPLY_CALLBACK) (
		pfTransactionReplyCallback,
		pnExtendedErrorCode, lpstrErrorMessage,
		dwErrorMessageSize);
}

long Trans2QuikAPI::IS_QUIK_CONNECTED(long* pnExtendedErrorCode,
		LPSTR lpstrErrorMessage, DWORD dwErrorMessageSize)
{
	return FNPA(IS_QUIK_CONNECTED)(pnExtendedErrorCode,
		lpstrErrorMessage, dwErrorMessageSize);
}

long Trans2QuikAPI::IS_DLL_CONNECTED(long* pnExtendedErrorCode,
		LPSTR lpstrErrorMessage, DWORD dwErrorMessageSize)
{
	return FNPA(IS_DLL_CONNECTED)(pnExtendedErrorCode,
		lpstrErrorMessage, dwErrorMessageSize);
}

long Trans2QuikAPI::SUBSCRIBE_ORDERS(LPSTR ClassCode, LPSTR Seccodes) {
	return FNPA(SUBSCRIBE_ORDERS)(ClassCode, Seccodes);
}

long Trans2QuikAPI::UNSUBSCRIBE_ORDERS() {
	return FNPA(UNSUBSCRIBE_ORDERS)();
}

long Trans2QuikAPI::START_ORDERS(
		TRANS2QUIK_ORDER_STATUS_CALLBACK pfnOrderStatusCallback)
{
	return FNPA(START_ORDERS)(pfnOrderStatusCallback);
}

long Trans2QuikAPI::ORDER_QTY (long nOrderDescriptor) {
	return FNPA(ORDER_QTY) (nOrderDescriptor);
}

long Trans2QuikAPI::ORDER_DATE(long nOrderDescriptor) {
	return FNPA(ORDER_DATE)(nOrderDescriptor);
}

long Trans2QuikAPI::ORDER_TIME(long nOrderDescriptor) {
	return FNPA(ORDER_TIME)(nOrderDescriptor);
}

long Trans2QuikAPI::ORDER_ACTIVATION_TIME(long nOrderDescriptor) {
	return FNPA(ORDER_ACTIVATION_TIME)(nOrderDescriptor);
}

long Trans2QuikAPI::ORDER_WITHDRAW_TIME(long nOrderDescriptor) {
	return FNPA(ORDER_WITHDRAW_TIME)(nOrderDescriptor);
}

long Trans2QuikAPI::ORDER_EXPIRY(long nOrderDescriptor) {
	return FNPA(ORDER_EXPIRY)(nOrderDescriptor);
}

double Trans2QuikAPI::ORDER_ACCRUED_INT(long nOrderDescriptor) {
	return FNPA(ORDER_ACCRUED_INT)(nOrderDescriptor);
}

double Trans2QuikAPI::ORDER_YIELD(long nOrderDescriptor) {
	return FNPA(ORDER_YIELD)(nOrderDescriptor);
}

long Trans2QuikAPI::ORDER_UID(long nOrderDescriptor) {
	return FNPA(ORDER_UID)(nOrderDescriptor);
}

LPTSTR Trans2QuikAPI::ORDER_USERID(long nOrderDescriptor) {
	return FNPA(ORDER_USERID)(nOrderDescriptor);
}

LPTSTR Trans2QuikAPI::ORDER_ACCOUNT(long nOrderDescriptor) {
	return FNPA(ORDER_ACCOUNT)(nOrderDescriptor);
}

LPTSTR Trans2QuikAPI::ORDER_BROKERREF(long nOrderDescriptor) {
	return FNPA(ORDER_BROKERREF)(nOrderDescriptor);
}

LPTSTR Trans2QuikAPI::ORDER_CLIENT_CODE(long nOrderDescriptor) {
	return FNPA(ORDER_CLIENT_CODE)(nOrderDescriptor);
}

LPTSTR Trans2QuikAPI::ORDER_FIRMID(long nOrderDescriptor) {
	return FNPA(ORDER_FIRMID)(nOrderDescriptor);
}

long Trans2QuikAPI::SUBSCRIBE_TRADES(LPSTR ClassCode, LPSTR Seccodes) {
	return FNPA(SUBSCRIBE_TRADES)(ClassCode, Seccodes);
}

long Trans2QuikAPI::UNSUBSCRIBE_TRADES() {
	return FNPA(UNSUBSCRIBE_TRADES)();
}

long Trans2QuikAPI::START_TRADES(
		TRANS2QUIK_TRADE_STATUS_CALLBACK pfnTradeStatusCallback)
{
	return FNPA(START_TRADES)(pfnTradeStatusCallback);
}

long Trans2QuikAPI::TRADE_DATE(long nTradeDescriptor) {
	return FNPA(TRADE_DATE)(nTradeDescriptor);
}

long Trans2QuikAPI::TRADE_SETTLE_DATE(long nTradeDescriptor) {
	return FNPA(TRADE_SETTLE_DATE)(nTradeDescriptor);
}

long Trans2QuikAPI::TRADE_TIME(long nTradeDescriptor) {
	return FNPA(TRADE_TIME)(nTradeDescriptor);
}

long Trans2QuikAPI::TRADE_IS_MARGINAL(long nTradeDescriptor) {
	return FNPA(TRADE_IS_MARGINAL)(nTradeDescriptor);
}

double Trans2QuikAPI::TRADE_ACCRUED_INT(long nTradeDescriptor) {
	return FNPA(TRADE_ACCRUED_INT)(nTradeDescriptor);
}

double Trans2QuikAPI::TRADE_YIELD(long nTradeDescriptor) {
	return FNPA(TRADE_YIELD)(nTradeDescriptor);
}

double Trans2QuikAPI::TRADE_TS_COMMISSION(long nTradeDescriptor) {
	return FNPA(TRADE_TS_COMMISSION)(nTradeDescriptor);
}

double Trans2QuikAPI::TRADE_CLEARING_CENTER_COMMISSION
	(long nTradeDescriptor)
{
	return FNPA(TRADE_CLEARING_CENTER_COMMISSION)(nTradeDescriptor);
}

double Trans2QuikAPI::TRADE_EXCHANGE_COMMISSION(long nTradeDescriptor) {
	return FNPA(TRADE_EXCHANGE_COMMISSION)(nTradeDescriptor);
}

double Trans2QuikAPI::TRADE_TRADING_SYSTEM_COMMISSION
	(long nTradeDescriptor)
{
	return FNPA(TRADE_TRADING_SYSTEM_COMMISSION)(nTradeDescriptor);
}

double Trans2QuikAPI::TRADE_PRICE2(long nTradeDescriptor) {
	return FNPA(TRADE_PRICE2)(nTradeDescriptor);
}

double Trans2QuikAPI::TRADE_REPO_RATE(long nTradeDescriptor) {
	return FNPA(TRADE_REPO_RATE)(nTradeDescriptor);
}

double Trans2QuikAPI::TRADE_REPO_VALUE(long nTradeDescriptor) {
	return FNPA(TRADE_REPO_VALUE)(nTradeDescriptor);
}

double Trans2QuikAPI::TRADE_REPO2_VALUE(long nTradeDescriptor) {
	return FNPA(TRADE_REPO2_VALUE)(nTradeDescriptor);
}

double Trans2QuikAPI::TRADE_ACCRUED_INT2(long nTradeDescriptor) {
	return FNPA(TRADE_ACCRUED_INT2)(nTradeDescriptor);
}

long Trans2QuikAPI::TRADE_REPO_TERM(long nTradeDescriptor) {
	return FNPA(TRADE_REPO_TERM)(nTradeDescriptor);
}

double Trans2QuikAPI::TRADE_START_DISCOUNT(long nTradeDescriptor) {
	return FNPA(TRADE_START_DISCOUNT)(nTradeDescriptor);
}

double Trans2QuikAPI::TRADE_LOWER_DISCOUNT(long nTradeDescriptor) {
	return FNPA(TRADE_LOWER_DISCOUNT)(nTradeDescriptor);
}

double Trans2QuikAPI::TRADE_UPPER_DISCOUNT(long nTradeDescriptor) {
	return FNPA(TRADE_UPPER_DISCOUNT)(nTradeDescriptor);
}

long Trans2QuikAPI::TRADE_BLOCK_SECURITIES(long nTradeDescriptor) {
	return FNPA(TRADE_BLOCK_SECURITIES)(nTradeDescriptor);
}

LPTSTR Trans2QuikAPI::TRADE_CURRENCY(long nTradeDescriptor) {
	return FNPA(TRADE_CURRENCY)(nTradeDescriptor);
}

LPTSTR Trans2QuikAPI::TRADE_SETTLE_CURRENCY(long nTradeDescriptor) {
	return FNPA(TRADE_SETTLE_CURRENCY)(nTradeDescriptor);
}

LPTSTR Trans2QuikAPI::TRADE_SETTLE_CODE(long nTradeDescriptor) {
	return FNPA(TRADE_SETTLE_CODE)(nTradeDescriptor);
}

LPTSTR Trans2QuikAPI::TRADE_ACCOUNT(long nTradeDescriptor) {
	return FNPA(TRADE_ACCOUNT)(nTradeDescriptor);
}

LPTSTR Trans2QuikAPI::TRADE_BROKERREF(long nTradeDescriptor) {
	return FNPA(TRADE_BROKERREF)(nTradeDescriptor);
}

LPTSTR Trans2QuikAPI::TRADE_CLIENT_CODE(long nTradeDescriptor) {
	return FNPA(TRADE_CLIENT_CODE)(nTradeDescriptor);
}

LPTSTR Trans2QuikAPI::TRADE_USERID(long nTradeDescriptor) {
	return FNPA(TRADE_USERID)(nTradeDescriptor);
}

LPTSTR Trans2QuikAPI::TRADE_FIRMID(long nTradeDescriptor) {
	return FNPA(TRADE_FIRMID)(nTradeDescriptor);
}

LPTSTR Trans2QuikAPI::TRADE_PARTNER_FIRMID(long nTradeDescriptor) {
	return FNPA(TRADE_PARTNER_FIRMID)(nTradeDescriptor);
}

LPTSTR Trans2QuikAPI::TRADE_EXCHANGE_CODE(long nTradeDescriptor) {
	return FNPA(TRADE_EXCHANGE_CODE)(nTradeDescriptor);
}

LPTSTR Trans2QuikAPI::TRADE_STATION_ID(long nTradeDescriptor) {
	return FNPA(TRADE_STATION_ID)(nTradeDescriptor);
}

} // end namespace wquik
