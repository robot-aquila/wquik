#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string.h>
#include "wquik/TransactionDriver.h"
#include "MockTrans2QuikAPI.h"
#include "MockQuikCallbackAPI.h"
#include "MockTransactionDriverCallback.h"

using namespace testing;
using namespace wquik;

class Helper_SetConnectionStatusCallback {
public:
	long FN(TRANS2QUIK_CONNECTION_STATUS_CALLBACK,
		long* pnExtendedErrorCode, LPSTR lpstrErrorMessage,
		DWORD dwErrorMessageSize)
	{
		sprintf_s(lpstrErrorMessage, dwErrorMessageSize, "zuzuka test");
		*pnExtendedErrorCode = 123;
		return TRANS2QUIK_FAILED;
	}
};

class Helper_Connect {
public:
	long FN(LPSTR lpstConnectionParamsString,
		long* pnExtendedErrorCode, LPSTR lpstrErrorMessage,
		DWORD dwErrorMessageSize)
	{
		sprintf_s(lpstrErrorMessage, dwErrorMessageSize, "zuzubaba");
		*pnExtendedErrorCode = 321;
		return TRANS2QUIK_FAILED;
	}
};

class Helper_Disconnect {
public:
	long FN(long* pnExtendedErrorCode, LPSTR lpstrErrorMessage,
		DWORD dwErrorMessageSize)
	{
		sprintf_s(lpstrErrorMessage, dwErrorMessageSize, "error error");
		*pnExtendedErrorCode = 555;
		return TRANS2QUIK_FAILED;
	}
};

class Helper_IsXxxConnected {
public:
	long FN(long* pnExtendedErrorCode, LPSTR lpstrErrorMessage,
		DWORD dwErrorMessageSize)
	{
		sprintf_s(lpstrErrorMessage, dwErrorMessageSize, "disconnected");
		*pnExtendedErrorCode = 111;
		return TRANS2QUIK_DLL_NOT_CONNECTED;
	}
};

class Helper_SendSyncTransaction {
public:
	long OK(LPSTR lpstTransactionString,
		long* pnReplyCode, PDWORD pdwTransId, double* pdOrderNum,
		LPSTR lpstrResultMessage, DWORD dwResultMessageSize,
		long* pnExtendedErrorCode, LPSTR lpstErrorMessage,
		DWORD dwErrorMessageSize)
	{
		*pnReplyCode = 3;
		*pdwTransId = 100500;
		*pdOrderNum = 1.34;
		sprintf_s(lpstrResultMessage, dwResultMessageSize, "OK");
		return TRANS2QUIK_SUCCESS;
	}

	long NOK(LPSTR lpstTransactionString,
		long* pnReplyCode, PDWORD pdwTransId, double* pdOrderNum,
		LPSTR lpstrResultMessage, DWORD dwResultMessageSize,
		long* pnExtendedErrorCode, LPSTR lpstErrorMessage,
		DWORD dwErrorMessageSize)
	{
		*pnExtendedErrorCode = 10;
		sprintf_s(lpstErrorMessage, dwErrorMessageSize, "ERROR");
		return TRANS2QUIK_FAILED;
	}
};

class Helper_SendAsyncTransaction {
public:
	long NOK(LPSTR lpstTransactionString, long* pnExtendedErrorCode,
		LPSTR lpstErrorMessage, DWORD dwErrorMessageSize)
	{
		*pnExtendedErrorCode = 12345;
		sprintf_s(lpstErrorMessage, dwErrorMessageSize, "FAILED");
		return TRANS2QUIK_FAILED;
	}
};


class TransactionDriverTest : public ::testing::Test {
protected:
	MockTrans2QuikAPI quik;
	MockQuikCallbackAPI callback;
	MockTransactionDriverCallback cb;
	TransactionDriver* driver;

	virtual void SetUp() {
		driver = 0;
		order = 0;
		trade = 0;
	}

	virtual void TearDown() {
		if ( driver != 0 ) {
			EXPECT_DESTRUCTOR_CALLS();
			driver->drop();
		}
		if ( order != 0 ) {
			order->drop();
		}
		if ( trade != 0 ) {
			trade->drop();
		}
	}

	void EXPECT_CONSTRUCTOR_CALLS() {
		EXPECT_CALL(callback, getConnectionStatusCallback())
			.Times(1)
			.WillOnce(Return((TRANS2QUIK_CONNECTION_STATUS_CALLBACK)555));
		EXPECT_CALL(quik, SET_CONNECTION_STATUS_CALLBACK
				((TRANS2QUIK_CONNECTION_STATUS_CALLBACK)555, _, _, _))
			.Times(1)
			.WillOnce(Return(TRANS2QUIK_SUCCESS));

		EXPECT_CALL(callback, setHandler(_)).Times(1);
	}

	void EXPECT_DESTRUCTOR_CALLS() {
		EXPECT_CALL(quik, DISCONNECT(_, _, _))
			.Times(1)
			.WillOnce(Return(TRANS2QUIK_SUCCESS));
	}

	void EXPECT_SET_SYNC_MODE_CALLS() {
		EXPECT_CALL(quik, SET_TRANSACTIONS_REPLY_CALLBACK
			((TRANS2QUIK_TRANSACTION_REPLY_CALLBACK)0, _, _, _))
			.Times(1)
			.WillOnce(Return(TRANS2QUIK_SUCCESS));
	}

	void EXPECT_SET_ASYNC_MODE_CALLS() {
		EXPECT_CALL(callback, getTransactionsReplyCallback())
			.Times(1)
			.WillOnce(Return((TRANS2QUIK_TRANSACTION_REPLY_CALLBACK)1122));
		EXPECT_CALL(quik, SET_TRANSACTIONS_REPLY_CALLBACK
			((TRANS2QUIK_TRANSACTION_REPLY_CALLBACK)1122, _, _, _))
			.Times(1)
			.WillOnce(Return(TRANS2QUIK_SUCCESS));
	}

public:
	void check_onTransactionReplyCallback(long result, long errorCode,
		const TransactionResult* tr);
	void check_onOrderStatusCallback(long mode, IOrder* order);
	void check_onTradeStatusCallback(long mode, ITrade* trade);
	IOrder* order;
	ITrade* trade;
};

TEST_F(TransactionDriverTest, testFailedConstructor) {
	Helper_SetConnectionStatusCallback helper;

	EXPECT_CALL(callback, getConnectionStatusCallback())
		.Times(1)
		.WillOnce(Return((TRANS2QUIK_CONNECTION_STATUS_CALLBACK)555));
	EXPECT_CALL(quik, SET_CONNECTION_STATUS_CALLBACK(_, _, _, _))
		.Times(1)
		.WillOnce(Invoke(&helper, &Helper_SetConnectionStatusCallback::FN));

	ASSERT_THROW(driver = new TransactionDriver(&quik, &callback),
		TransactionDriverException);
}

TEST_F(TransactionDriverTest, testDefaultConstructor) {
	EXPECT_CONSTRUCTOR_CALLS();

	driver = new TransactionDriver(&quik, &callback);
	ASSERT_EQ(2, callback.getRefCount());
	ASSERT_EQ(2, quik.getRefCount());
	ASSERT_TRUE(driver->isSyncMode());
	ASSERT_FALSE(driver->isAsyncMode());
}

TEST_F(TransactionDriverTest, testSetAsyncMode) {
	EXPECT_CONSTRUCTOR_CALLS();

	EXPECT_CALL(callback, getTransactionsReplyCallback())
		.Times(1)
		.WillOnce(Return((TRANS2QUIK_TRANSACTION_REPLY_CALLBACK)1122));
	EXPECT_CALL(quik, SET_TRANSACTIONS_REPLY_CALLBACK
		((TRANS2QUIK_TRANSACTION_REPLY_CALLBACK)1122, _, _, _))
		.Times(1)
		.WillOnce(Return(TRANS2QUIK_SUCCESS));

	driver = new TransactionDriver(&quik, &callback);
	driver->setAsyncMode();
	ASSERT_TRUE(driver->isAsyncMode());
	ASSERT_FALSE(driver->isSyncMode());
}

TEST_F(TransactionDriverTest, testSetSyncMode) {
	EXPECT_CONSTRUCTOR_CALLS();

	EXPECT_CALL(quik, SET_TRANSACTIONS_REPLY_CALLBACK
		((TRANS2QUIK_TRANSACTION_REPLY_CALLBACK)0, _, _, _))
		.Times(1)
		.WillOnce(Return(TRANS2QUIK_SUCCESS));

	driver = new TransactionDriver(&quik, &callback);
	driver->setSyncMode();
	ASSERT_TRUE(driver->isSyncMode());
	ASSERT_FALSE(driver->isAsyncMode());
}


TEST_F(TransactionDriverTest, testConnectSuccess) {
	EXPECT_CONSTRUCTOR_CALLS();

	EXPECT_CALL(quik, CONNECT("/path/to/quik", _, _, _))
		.Times(1)
		.WillOnce(Return(TRANS2QUIK_SUCCESS));
	EXPECT_CALL(quik, SUBSCRIBE_ORDERS("", "")).Times(1);
	EXPECT_CALL(quik, SUBSCRIBE_TRADES("", "")).Times(1);

	EXPECT_CALL(callback, getOrderStatusCallback()).Times(1)
		.WillOnce(Return((TRANS2QUIK_ORDER_STATUS_CALLBACK)555));
	EXPECT_CALL(quik, START_ORDERS((TRANS2QUIK_ORDER_STATUS_CALLBACK)555))
		.Times(1);

	EXPECT_CALL(callback, getTradeStatusCallback()).Times(1)
		.WillOnce(Return((TRANS2QUIK_TRADE_STATUS_CALLBACK)444));
	EXPECT_CALL(quik, START_TRADES((TRANS2QUIK_TRADE_STATUS_CALLBACK)444))
		.Times(1);

	driver = new TransactionDriver(&quik, &callback);
	driver->connect("/path/to/quik");
}

TEST_F(TransactionDriverTest, testConnectFailed) {
	Helper_Connect helper;
	EXPECT_CONSTRUCTOR_CALLS();

	EXPECT_CALL(quik, CONNECT("/path/to/quik", _, _, _))
		.Times(1)
		.WillOnce(Invoke(&helper, &Helper_Connect::FN));

	driver = new TransactionDriver(&quik, &callback);
	ASSERT_THROW(driver->connect("/path/to/quik"), TransactionDriverException);
}

TEST_F(TransactionDriverTest, testDisconnectSuccess) {
	EXPECT_CONSTRUCTOR_CALLS();

	EXPECT_CALL(quik, DISCONNECT(_, _, _))
		.Times(1)
		.WillOnce(Return(TRANS2QUIK_SUCCESS));

	driver = new TransactionDriver(&quik, &callback);
	driver->disconnect();
}

TEST_F(TransactionDriverTest, testDisconnectFailed) {
	Helper_Disconnect helper;
	EXPECT_CONSTRUCTOR_CALLS();

	EXPECT_CALL(quik, DISCONNECT(_, _, _))
		.Times(1)
		.WillOnce(Invoke(&helper, &Helper_Disconnect::FN));

	driver = new TransactionDriver(&quik, &callback);
	ASSERT_THROW(driver->disconnect(), TransactionDriverException);
}

TEST_F(TransactionDriverTest, testIsDllConnectedIfConnected) {
	EXPECT_CONSTRUCTOR_CALLS();

	EXPECT_CALL(quik, IS_DLL_CONNECTED(_, _, _))
		.Times(1)
		.WillOnce(Return(TRANS2QUIK_DLL_CONNECTED));

	driver = new TransactionDriver(&quik, &callback);
	ASSERT_TRUE(driver->isDllConnected());
}

TEST_F(TransactionDriverTest, testIsDllConnectedIfDisconnected) {
	Helper_IsXxxConnected helper;
	EXPECT_CONSTRUCTOR_CALLS();

	EXPECT_CALL(quik, IS_DLL_CONNECTED(_, _, _))
		.Times(1)
		.WillOnce(Invoke(&helper, &Helper_IsXxxConnected::FN));

	driver = new TransactionDriver(&quik, &callback);
	ASSERT_FALSE(driver->isDllConnected());
}

TEST_F(TransactionDriverTest, testIsQuikConnectedIfConnected) {
	EXPECT_CONSTRUCTOR_CALLS();

	EXPECT_CALL(quik, IS_QUIK_CONNECTED(_, _, _))
		.Times(1)
		.WillOnce(Return(TRANS2QUIK_QUIK_CONNECTED));

	driver = new TransactionDriver(&quik, &callback);
	ASSERT_TRUE(driver->isQuikConnected());
}

TEST_F(TransactionDriverTest, testIsQuikConnectedIfDisconnected) {
	Helper_IsXxxConnected helper;
	EXPECT_CONSTRUCTOR_CALLS();

	EXPECT_CALL(quik, IS_QUIK_CONNECTED(_, _, _))
		.Times(1)
		.WillOnce(Invoke(&helper, &Helper_IsXxxConnected::FN));

	driver = new TransactionDriver(&quik, &callback);
	ASSERT_FALSE(driver->isQuikConnected());
}

TEST_F(TransactionDriverTest, testSendSyncTransactionSuccess) {
	Helper_SendSyncTransaction helper;
	EXPECT_CONSTRUCTOR_CALLS();

	EXPECT_CALL(quik, SEND_SYNC_TRANSACTION
		("TRANS STR", _, _, _, _, _, _, _, _))
		.Times(1)
		.WillOnce(Invoke(&helper, &Helper_SendSyncTransaction::OK));

	TransactionResult tr;
	driver = new TransactionDriver(&quik, &callback);
	driver->sendSyncTransaction("TRANS STR", &tr);

	ASSERT_EQ(3, tr.replyCode);
	ASSERT_EQ(100500, tr.transId);
	ASSERT_EQ(1.34, tr.orderNumber);
	ASSERT_EQ(std::string("OK"), tr.resultMessage);
}

TEST_F(TransactionDriverTest, testSendSyncTransactionFailed) {
	Helper_SendSyncTransaction helper;
	EXPECT_CONSTRUCTOR_CALLS();

	EXPECT_CALL(quik, SEND_SYNC_TRANSACTION
		("TRANS STR", _, _, _, _, _, _, _, _))
		.Times(1)
		.WillOnce(Invoke(&helper, &Helper_SendSyncTransaction::NOK));

	TransactionResult tr;
	driver = new TransactionDriver(&quik, &callback);
	ASSERT_THROW(driver->sendSyncTransaction("TRANS STR", &tr),
		TransactionDriverException);
}

TEST_F(TransactionDriverTest, testSendSyncTransactionInAsyncModeThrows) {
	EXPECT_CONSTRUCTOR_CALLS();
	EXPECT_SET_ASYNC_MODE_CALLS();

	TransactionResult tr;
	driver = new TransactionDriver(&quik, &callback);
	driver->setAsyncMode();
	ASSERT_THROW(driver->sendSyncTransaction("TRANS STR", &tr),
		TransactionDriverException);
}

TEST_F(TransactionDriverTest, testSendAsyncTransactionSuccess) {
	EXPECT_CONSTRUCTOR_CALLS();
	EXPECT_SET_ASYNC_MODE_CALLS();

	EXPECT_CALL(quik, SEND_ASYNC_TRANSACTION("TRANS STR", _, _, _))
		.Times(1)
		.WillOnce(Return(TRANS2QUIK_SUCCESS));

	driver = new TransactionDriver(&quik, &callback);
	driver->setAsyncMode();
	driver->sendAsyncTransaction("TRANS STR");
}

TEST_F(TransactionDriverTest, testSendAsyncTransactionFailed) {
	Helper_SendAsyncTransaction helper;
	EXPECT_CONSTRUCTOR_CALLS();
	EXPECT_SET_ASYNC_MODE_CALLS();

	EXPECT_CALL(quik, SEND_ASYNC_TRANSACTION("TRANS STR", _, _, _))
		.Times(1)
		.WillOnce(Invoke(&helper, &Helper_SendAsyncTransaction::NOK));

	driver = new TransactionDriver(&quik, &callback);
	driver->setAsyncMode();
	ASSERT_THROW(driver->sendAsyncTransaction("TRANS STR"),
		TransactionDriverException);
}

TEST_F(TransactionDriverTest, testSendAsyncTransactionIsSyncModeThrows) {
	EXPECT_CONSTRUCTOR_CALLS();

	driver = new TransactionDriver(&quik, &callback);
	ASSERT_THROW(driver->sendAsyncTransaction("TRANS STR"),
		TransactionDriverException);
}

TEST_F(TransactionDriverTest, testOnConnectionStatusCallback) {
	EXPECT_CONSTRUCTOR_CALLS();

	EXPECT_CALL(cb, onConnectionStatus(5, 10, "foobar")).Times(1);
	
	driver = new TransactionDriver(&quik, &callback);
	driver->setCallbackHandler(&cb);
	driver->onConnectionStatus(5, 10, "foobar");
}

TEST_F(TransactionDriverTest, testOnConnectionStatusCallbackIfNoHandler) {
	EXPECT_CONSTRUCTOR_CALLS();

	driver = new TransactionDriver(&quik, &callback);
	driver->onConnectionStatus(5, 10, "barfoo");
}

TEST_F(TransactionDriverTest, testOnTransactionReplyCallbackIfNoHandler) {
	EXPECT_CONSTRUCTOR_CALLS();

	driver = new TransactionDriver(&quik, &callback);
	driver->onTransactionReply(1, 2, 3, 4, 5.6, "zuzuka");
}

void TransactionDriverTest::check_onTransactionReplyCallback(long result,
	long errorCode,	const TransactionResult* tr)
{
	ASSERT_EQ(123, result);
	ASSERT_EQ(321, errorCode);
	ASSERT_EQ(888, tr->replyCode);
	ASSERT_EQ(999, tr->transId);
	ASSERT_EQ(11.22, tr->orderNumber);
	ASSERT_EQ(std::string("OKI"), tr->resultMessage);
}

TEST_F(TransactionDriverTest, testOnTransactionReplyCallback) {
	EXPECT_CONSTRUCTOR_CALLS();

	EXPECT_CALL(cb, onTransactionReply(_,_,_))
		.Times(1)
		.WillOnce(Invoke(&(*this),
			&TransactionDriverTest::check_onTransactionReplyCallback));

	driver = new TransactionDriver(&quik, &callback);
	driver->setCallbackHandler(&cb);
	driver->onTransactionReply(123, 321, 888, 999, 11.22, "OKI");
}

TEST_F(TransactionDriverTest, testOnOrderStatusCallbackIfNoHandler) {
	EXPECT_CONSTRUCTOR_CALLS();

	driver = new TransactionDriver(&quik, &callback);
	driver->onOrderStatus(1, 2, 3.4, "ERBR", "SBER", 10.15, 100, 200, 0, 8, 9);
}

void TransactionDriverTest::check_onOrderStatusCallback
	(long mode, IOrder* order)
{
	this->order = (IOrder*)order->grab();
	ASSERT_EQ(2, order->getRefCount());
	ASSERT_EQ(123, mode);
	ASSERT_STREQ("ACCOUNT", order->getAccount());

	ASSERT_EQ(222, order->getTransId());
	ASSERT_EQ(33.44, order->getNumber());
	ASSERT_STREQ("BRBR", order->getClassCode());
	ASSERT_STREQ("ROSN", order->getSecCode());
	ASSERT_EQ(44.55, order->getPrice());
	ASSERT_EQ(1111, order->getBalance());
	ASSERT_EQ(6666.55, order->getValue());
	ASSERT_TRUE(order->isSell());
	ASSERT_EQ(888999, order->getStatus());
}

TEST_F(TransactionDriverTest, testOnOrderStatusCallback) {
	EXPECT_CONSTRUCTOR_CALLS();

	EXPECT_CALL(cb, onOrderStatus(_, _))
		.Times(1)
		.WillOnce(Invoke(&(*this),
			&TransactionDriverTest::check_onOrderStatusCallback));
	EXPECT_CALL(quik, ORDER_ACCOUNT(777))
		.Times(1)
		.WillOnce(Return((char*)"ACCOUNT"));

	driver = new TransactionDriver(&quik, &callback);
	driver->setCallbackHandler(&cb);
	driver->onOrderStatus(123, 222, 33.44, "BRBR", "ROSN",
		44.55, 1111, 6666.55, 1, 888999, 777);
	ASSERT_NE((IOrder*)0, order); // обработчик должен быть вызван
	ASSERT_EQ(1, order->getRefCount()); // обработчик должен освободить инстанс
}

TEST_F(TransactionDriverTest, testOnTradeStatusCallbackIfNoHandler) {
	EXPECT_CONSTRUCTOR_CALLS();

	driver = new TransactionDriver(&quik, &callback);
	driver->onTradeStatus(1, 2.3, 3.4, "ERBR", "SBER",
		10.15, 100, 200.11, 0, 9);
}

void TransactionDriverTest::check_onTradeStatusCallback
	(long mode, ITrade* trade)
{
	this->trade = (ITrade*)trade->grab();
	ASSERT_EQ(2, trade->getRefCount());
	ASSERT_EQ(1, mode);
	ASSERT_STREQ("ACCOUNT", trade->getAccount());

	ASSERT_EQ(2.3, trade->getNumber());
	ASSERT_EQ(3.4, trade->getOrderNumber());
	ASSERT_STREQ("ERBR", trade->getClassCode());
	ASSERT_STREQ("SBER", trade->getSecCode());
	ASSERT_EQ(10.15, trade->getPrice());
	ASSERT_EQ(100, trade->getQty());
	ASSERT_EQ(200.11, trade->getValue());
	ASSERT_FALSE(trade->isSell());
}

TEST_F(TransactionDriverTest, testOnTradeStatusCallback) {
	EXPECT_CONSTRUCTOR_CALLS();

	EXPECT_CALL(cb, onTradeStatus(_, _))
		.Times(1)
		.WillOnce(Invoke(&(*this),
			&TransactionDriverTest::check_onTradeStatusCallback));
	EXPECT_CALL(quik, TRADE_ACCOUNT(9))
		.Times(1)
		.WillOnce(Return((char*)"ACCOUNT"));

	driver = new TransactionDriver(&quik, &callback);
	driver->setCallbackHandler(&cb);
	driver->onTradeStatus(1, 2.3, 3.4, "ERBR", "SBER",
		10.15, 100, 200.11, 0, 9);
	ASSERT_NE((ITrade*)0, trade); // обработчик должен быть вызван
	ASSERT_EQ(1, trade->getRefCount()); // обработчик должен освободить инстанс
}

