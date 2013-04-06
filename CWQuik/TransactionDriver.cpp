#include "wquik/TransactionDriver.h"
#include "wquik/Order.h"
#include "wquik/Trade.h"

namespace wquik {

TransactionDriver::TransactionDriver
	(ITrans2QuikAPI* quik, IQuikCallbackAPI* callback)
{
	long res,exterr;
	char msg[255];
	res = quik->SET_CONNECTION_STATUS_CALLBACK
		(callback->getConnectionStatusCallback(), &exterr, msg, sizeof(msg));
	if ( res != TRANS2QUIK_SUCCESS ) {
		throw TransactionDriverException(msg);
	}
	_quik = (ITrans2QuikAPI*)quik->grab();
	_callback = (IQuikCallbackAPI*)callback->grab();
	_callback->setHandler(this);
	_isSyncMode = true;
	_callbackHandler = 0;
}

TransactionDriver::~TransactionDriver(void) {
	disconnect();
	_callback->drop();
	_quik->drop();
}

void TransactionDriver::setAsyncMode() {
	setTransactionReplyCallback(_callback->getTransactionsReplyCallback());
	_isSyncMode = false;
}

void TransactionDriver::setSyncMode() {
	setTransactionReplyCallback(0);
	_isSyncMode = true;
}

bool TransactionDriver::isSyncMode() {
	return _isSyncMode;
}

bool TransactionDriver::isAsyncMode() {
	return ! _isSyncMode;
}

void TransactionDriver::connect(const char* path) {
	long res,exterr;
	char msg[255];
	res = _quik->CONNECT((LPSTR)((void*)path), &exterr, msg, sizeof(msg));
	if ( res != TRANS2QUIK_SUCCESS
		&& res != TRANS2QUIK_ALREADY_CONNECTED_TO_QUIK )
	{
		throw TransactionDriverException(msg);
	}
	_quik->SUBSCRIBE_ORDERS("", "");
	_quik->SUBSCRIBE_TRADES("", "");
	_quik->START_ORDERS(_callback->getOrderStatusCallback());
	_quik->START_TRADES(_callback->getTradeStatusCallback());
}

void TransactionDriver::disconnect() {
	long res,exterr;
	char msg[255];
	res = _quik->DISCONNECT(&exterr, msg, sizeof(msg));
	if ( res != TRANS2QUIK_SUCCESS
		&& res != TRANS2QUIK_DLL_NOT_CONNECTED )
	{
		throw TransactionDriverException(msg);
	}
}

bool TransactionDriver::isQuikConnected() {
	long res,exterr;
	char msg[255];
	res = _quik->IS_QUIK_CONNECTED(&exterr, msg, sizeof(msg));
	return res == TRANS2QUIK_QUIK_CONNECTED;
}

bool TransactionDriver::isDllConnected() {
	long res,exterr;
	char msg[255];
	res = _quik->IS_DLL_CONNECTED(&exterr, msg, sizeof(msg));
	return res == TRANS2QUIK_DLL_CONNECTED;
}

void TransactionDriver::sendSyncTransaction(const char* str, TransactionResult* tr) {
	long res,exterr;
	char msg[255];
	char resultMsg[255];
	if ( ! _isSyncMode ) {
		throw TransactionDriverException
			("The driver currently in asynchronous mode");
	}

	res = _quik->SEND_SYNC_TRANSACTION((char*)(void*)str, &tr->replyCode,
		&tr->transId, &tr->orderNumber, resultMsg, sizeof(resultMsg), &exterr,
		msg, sizeof(msg));
	if ( res != TRANS2QUIK_SUCCESS ) {
		throw TransactionDriverException(msg);
	}
	tr->resultMessage.assign(resultMsg);
}

void TransactionDriver::sendAsyncTransaction(const char* str) {
	long res,exterr;
	char msg[255];
	if ( _isSyncMode ) {
		throw TransactionDriverException
			("The driver currently in synchronous mode");
	}
	res = _quik->SEND_ASYNC_TRANSACTION((char*)(void*)str, &exterr,
		msg, sizeof(msg));
	if ( res != TRANS2QUIK_SUCCESS ) {
		throw TransactionDriverException(msg);
	}
}

void TransactionDriver::setCallbackHandler(ITransactionDriverCallback* cb) {
	_callbackHandler = cb;
}

void TransactionDriver::setTransactionReplyCallback
	(TRANS2QUIK_TRANSACTION_REPLY_CALLBACK cb)
{
	long res,exterr;
	char msg[255];
	res = _quik->SET_TRANSACTIONS_REPLY_CALLBACK
		(cb, &exterr, msg, sizeof(msg));
	if ( res != TRANS2QUIK_SUCCESS ) {
		throw TransactionDriverException(msg);
	}
}

void TransactionDriver::onConnectionStatus(long nConnectionEvent,
	long nExtendedErrorCode, LPSTR lpstrInfoMessage)
{
	if ( _callbackHandler != 0 ) {
		_callbackHandler->onConnectionStatus(nConnectionEvent,
			nExtendedErrorCode, lpstrInfoMessage);
	}
}

void TransactionDriver::onTransactionReply(long nTransactionResult,
	long nTransactionExtendedErrorCode, long nTransactionReplyCode,
	DWORD dwTransId, double dOrderNum, LPSTR lpstrTransactionReplyMessage)
{
	TransactionResult tr;
	if ( _callbackHandler != 0 ) {
		tr.replyCode = nTransactionReplyCode;
		tr.transId = dwTransId;
		tr.orderNumber = dOrderNum;
		tr.resultMessage.assign(lpstrTransactionReplyMessage);
		_callbackHandler->onTransactionReply(nTransactionResult,
			nTransactionExtendedErrorCode, &tr);
	}
}

void TransactionDriver::onOrderStatus(long nMode, DWORD dwTransID,
	double dNumber, LPSTR lpstrClassCode, LPSTR lpstrSecCode, double dPrice,
	long nBalance, double dValue, long nIsSell, long nStatus,
	long nOrderDescriptor)
{
	Order* order;
	if ( _callbackHandler != 0 ) {
		order = new Order(dwTransID, dNumber, lpstrClassCode, lpstrSecCode,
			dPrice, nBalance, dValue, (nIsSell == 0 ? false : true),
			nStatus, nOrderDescriptor, _quik);
		_callbackHandler->onOrderStatus(nMode, order);
		order->drop();
	}
}

void TransactionDriver::onTradeStatus(long nMode, double dNumber,
	double dOrderNum, LPSTR lpstrClassCode, LPSTR lpstrSecCode, double dPrice,
	long nQty, double dValue, long nIsSell, long nTradeDescriptor)
{
	Trade* trade;
	if ( _callbackHandler != 0 ) {
		trade = new Trade(dNumber, dOrderNum, lpstrClassCode, lpstrSecCode,
			dPrice, nQty, dValue, (nIsSell == 0 ? false : true),
			nTradeDescriptor, _quik);
		_callbackHandler->onTradeStatus(nMode, trade);
		trade->drop();
	}
}

} // end namespace wquik
