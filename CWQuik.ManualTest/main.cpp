#include <windows.h>
#include <gtest/gtest.h>
#include "wquik/WQuik.h"
#include "wquik/ITransactionDriver.h"
#include "config.h"

#define EID_PRIMARY_LOADED "PRIMARY_LOADED"

using namespace testing;
using namespace wquik;

void print_msg(const char* text) {
	SYSTEMTIME st;
	GetLocalTime(&st);
	printf("[%d] %02d:%02d:%02d.%03d %s\n", GetCurrentThreadId(),
		st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, text);
}

ULONGLONG get_time() {
	SYSTEMTIME st;
	FILETIME ft;
	GetSystemTime(&st);
	SystemTimeToFileTime(&st, &ft);
	ULARGE_INTEGER i;
	i.LowPart = ft.dwLowDateTime;
	i.HighPart = ft.dwHighDateTime;
	return i.QuadPart / 10000;
}

#define EXEC_TIME(cmd, desc) { \
	ULONGLONG st = get_time(); \
	cmd; \
	ULONGLONG tm = get_time() - st; \
	char msg[1024]; \
	sprintf_s(msg, sizeof(msg), "%s time %d ms.", desc, tm); \
	print_msg(msg); }
#define PULSE_EVENT(eventId) { \
	HANDLE hEvent = CreateEventA(NULL, FALSE, FALSE, eventId); \
	PulseEvent(hEvent); \
	CloseHandle(hEvent); }
#define WAIT_EVENT(eventId) { \
	HANDLE hEvent = CreateEventA(NULL, FALSE, FALSE, eventId); \
	DWORD res = WaitForSingleObject(hEvent, 20000); \
	CloseHandle(hEvent); \
	ASSERT_EQ(WAIT_OBJECT_0, res); }

class CallbackHandler : public ITransactionDriverCallback {
public:
	long lastId;
	bool ordersLoaded;
	bool tradesLoaded;

	CallbackHandler() {
		lastId = 0;
		ordersLoaded = tradesLoaded = false;
	}

	virtual ~CallbackHandler(void){}

	void noticePrimaryLoaded() {
		if ( ! ordersLoaded || ! tradesLoaded ) {
			return;
		}
		PULSE_EVENT(EID_PRIMARY_LOADED);
	}

	virtual void onConnectionStatus
		(long eventId, long errorCode, const char* message)
	{
		char msg[1024];
		sprintf_s(msg, sizeof(msg),
			"Connection status: event=%d, error=%d, msg=%s",
			eventId, errorCode, message);
		print_msg(msg);
	}

	virtual void onTransactionReply
		(long result, long errorCode, const TransactionResult* tr)
	{
		char msg[2048];
		sprintf_s(msg, sizeof(msg), "Transaction reply: result=%d, err=%d, "
			"replyCode=%d, transId=%d, orderNum=%f, msg=%s", result,
			errorCode, tr->replyCode, tr->transId, tr->orderNumber,
			tr->resultMessage.c_str());
		print_msg(msg);
	}

	virtual void onOrderStatus(long mode, IOrder* order) {
		char msg[2048];
		if ( mode == 0 ) {
			sprintf_s(msg, sizeof(msg), "Order status (mode=%d): transId=%d, "
				"number=%f, class=%s, sec=%s, price=%f, balance=%d, value=%f, "
				"isSell=%s, status=%d", mode, order->getTransId(),
				order->getNumber(), order->getClassCode(), order->getSecCode(),
				order->getPrice(), order->getBalance(), order->getValue(),
				(order->isSell() ? "yes" : "no"), order->getStatus());
			print_msg(msg);
		}
		if ( mode == 1 || mode == 2 ) {
			if ( order->getTransId() > lastId ) {
				lastId = order->getTransId();
			}
		}
		if ( mode == 2 ) {
			ordersLoaded = true;
			noticePrimaryLoaded();
		}
	}

	virtual void onTradeStatus(long mode, ITrade* trade) {
		char msg[2048];
		if ( mode == 0 ) {
			sprintf_s(msg, sizeof(msg), "Trade status (mode=%d): num=%f, "
				"orderNum=%f, class=%s, sec=%s, price=%f, qty=%d, value=%f, "
				"isSell=%s", mode, trade->getNumber(), trade->getOrderNumber(),
				trade->getClassCode(), trade->getSecCode(), trade->getPrice(),
				trade->getQty(), trade->getValue(),
				(trade->isSell() ? "yes" : "no"));
			print_msg(msg);
		}
		if ( mode == 2 ) {
			tradesLoaded = true;
			noticePrimaryLoaded();
		}
	}

};

class ManualTest : public ::testing::Test {
protected:
	ITransactionDriver* driver;
	CallbackHandler cb;

	virtual void SetUp() {
		print_msg("Test started");
		driver = 0;
		driver = WQuik::createDriver();
		driver->setCallbackHandler(&cb);
	}

	virtual void TearDown() {
		if ( driver == 0 ) {
			driver->setCallbackHandler(0);
			driver->drop();
		}
		print_msg("Test finished");
	}
};

TEST_F(ManualTest, testMain) {
	string str;
	char buf[2048];
	TransactionResult tr;

	printf("\n1. Test connect\n");
	printf("Start QUIK in %s directory and press RETURN...", QUIK_PATH);
	//getchar();
	EXEC_TIME(ASSERT_NO_THROW(driver->connect(QUIK_PATH)), "connect");
	// ожидаем первичной загрузки заявок и сделок
	WAIT_EVENT(EID_PRIMARY_LOADED);

	printf("\n2. Test asynchronous mode\n");
	cb.lastId ++;
	sprintf_s(buf, sizeof(buf), "ACCOUNT=%s; CLIENT_CODE=%s;"
		" TYPE=L; TRANS_ID=%d; CLASSCODE=%s; SECCODE=%s; ACTION=NEW_ORDER; "
		"OPERATION=B; QUANTITY=1; PRICE=%0.2f; ", QUIK_ACCOUNT,
		QUIK_CLIENT_CODE, cb.lastId, QUIK_CLASSCODE, QUIK_SECCODE, QUIK_PRICE);
	printf("%s\n", buf);
	EXEC_TIME(ASSERT_NO_THROW(driver->setAsyncMode()), "setAsyncMode");
	EXEC_TIME(ASSERT_NO_THROW
		(driver->sendAsyncTransaction(buf)), "sendAsyncTransaction");
	Sleep(5000);

	printf("\n3. Test synchronous mode\n");
	cb.lastId ++;
	sprintf_s(buf, sizeof(buf), "ACCOUNT=%s; CLIENT_CODE=%s;"
		" TYPE=L; TRANS_ID=%d; CLASSCODE=%s; SECCODE=%s; ACTION=NEW_ORDER; "
		"OPERATION=B; QUANTITY=1; PRICE=%0.2f; ", QUIK_ACCOUNT,
		QUIK_CLIENT_CODE, cb.lastId, QUIK_CLASSCODE, QUIK_SECCODE, QUIK_PRICE);
	printf("%s\n", buf);
	EXEC_TIME(ASSERT_NO_THROW(driver->setSyncMode()), "setSyncMode");
	EXEC_TIME(ASSERT_NO_THROW(driver->sendSyncTransaction(buf, &tr)),
		"sendSyncTransaction");
	// В tr.replyCode не может быть 0, потому что, согласно документации,
	// при синхронном выполнении транзы возврат осуществляется только
	// после получения результата транзакции.
	ASSERT_EQ(3, tr.replyCode);
	ASSERT_EQ(cb.lastId, tr.transId);
	Sleep(5000);
}


int main( int argc, char* argv[] ) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
