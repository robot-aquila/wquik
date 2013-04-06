#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <jwquik/JavaWrapper.h>
#include "MockJavaHelper.h"
#include "MockTransactionDriver.h"
#include "MockWrapperStrategy.h"
#include "MockOrder.h"
#include "MockTrade.h"
#include "jwquik/DriverCallbackTransfer.h"

using namespace testing;

#define FAKE_JVM_PTR 554433
#define FAKE_OBJ_PTR 111111

class DriverCallbackTransferTest : public ::testing::Test {
public:
	MockJavaHelper helper;
	MockTransactionDriver driver;
	MockWrapperStrategy strategy;
	MockTrade trade;
	MockOrder order;
	jobject obj;

	virtual void SetUp() {
		if ( JavaWrapper::getStrategy() != &strategy ) {
			EXPECT_CALL(strategy, grab())
				.Times(1)
				.WillOnce(Return(&strategy));
			JavaWrapper::setStrategy(&strategy);
		}
		obj = (jobject)FAKE_OBJ_PTR;
	}

	virtual void TearDown() {
		EXPECT_CALL(strategy, drop())
			.Times(1)
			.WillOnce(Return(true));
		JavaWrapper::setStrategy(0);
	}

	void EXPECT_CONSTRUCTOR_CALLS() {
		EXPECT_CALL(helper, getJVM())
			.Times(1)
			.WillOnce(Return((JavaVM*)FAKE_JVM_PTR));
		EXPECT_CALL(helper, createGlobalRef(obj))
			.Times(1)
			.WillOnce(Return((jobject)FAKE_OBJ_PTR));
		EXPECT_CALL(driver, grab())
			.Times(1)
			.WillOnce(Return(&driver));
		EXPECT_CALL(driver, setCallbackHandler(_))
			.Times(1);
	}

	void EXPECT_DESTRUCTOR_CALLS() {
		EXPECT_CALL(strategy, produce((JavaVM*)FAKE_JVM_PTR))
			.Times(1)
			.WillOnce(Return(&helper));
		EXPECT_CALL(helper, deleteGlobalRef((jobject)FAKE_OBJ_PTR))
			.Times(1);
		EXPECT_CALL(helper, drop())
			.Times(1)
			.WillOnce(Return(true));
		EXPECT_CALL(driver, drop())
			.Times(1).
			WillOnce(Return(true));
	}
};

TEST_F(DriverCallbackTransferTest, testConstructor) {
	EXPECT_CONSTRUCTOR_CALLS();

	DriverCallbackTransfer transfer(&helper, &driver, obj);

	EXPECT_DESTRUCTOR_CALLS();
}

TEST_F(DriverCallbackTransferTest, testGetDriver) {
	EXPECT_CONSTRUCTOR_CALLS();

	DriverCallbackTransfer transfer(&helper, &driver, obj);
	ASSERT_EQ(&driver, transfer.getDriver());

	EXPECT_DESTRUCTOR_CALLS();
}

TEST_F(DriverCallbackTransferTest, testOnConnectionStatus) {
	EXPECT_CONSTRUCTOR_CALLS();
	EXPECT_CALL(strategy, produce((JavaVM*)FAKE_JVM_PTR))
		.Times(1)
		.WillOnce(Return(&helper));
	EXPECT_CALL(helper, getObjectField((jobject)FAKE_OBJ_PTR,
			StrCaseEq("callback"),
			StrCaseEq("Lru/prolib/JWQuik/ICallback;")))
		.Times(1)
		.WillOnce(Return((jobject)7788));
	EXPECT_CALL(helper, getMethodId((jobject)7788,
			StrCaseEq("onConnectionStatus"),
			StrCaseEq("(JJLjava/lang/String;)V")))
		.Times(1)
		.WillOnce(Return((jmethodID)6655));
	EXPECT_CALL(helper, toJstring(StrCaseEq("ZZZZ")))
		.Times(1)
		.WillOnce(Return((jstring)4433));
	EXPECT_CALL(helper, callVoidMethod_LLO
			((jobject)7788, (jmethodID)6655, 111, 222, (jstring)4433))
		.Times(1);
	EXPECT_CALL(helper, drop())
		.Times(1)
		.WillOnce(Return(true));

	DriverCallbackTransfer transfer(&helper, &driver, obj);
	transfer.onConnectionStatus(111, 222, "ZZZZ");

	EXPECT_DESTRUCTOR_CALLS();
}

TEST_F(DriverCallbackTransferTest, testOnTransactionReply) {
	TransactionResult tr;
	long result = 3;
	long errorCode = 235;
	tr.replyCode = 800;
	tr.transId = 100500;
	tr.orderNumber = 33.44;
	tr.resultMessage = "foobar";

	JavaVM* jvm = (JavaVM*)FAKE_JVM_PTR;
	jobject callback = (jobject)7788;
	jmethodID onTransactionReplyId = (jmethodID)6655;
	jstring jmessage = (jstring)555;
	jobject jtr = (jobject)7777;

	EXPECT_CONSTRUCTOR_CALLS();
	EXPECT_CALL(strategy, produce(jvm))
		.Times(1)
		.WillOnce(Return(&helper));
	EXPECT_CALL(helper, getObjectField((jobject)FAKE_OBJ_PTR,
			StrCaseEq("callback"),
			StrCaseEq("Lru/prolib/JWQuik/ICallback;")))
		.Times(1)
		.WillOnce(Return(callback));
	EXPECT_CALL(helper, getMethodId(callback,
			StrCaseEq("onTransactionReply"),
			StrCaseEq("(JJLru/prolib/JWQuik/ITransactionResult;)V")))
		.Times(1)
		.WillOnce(Return(onTransactionReplyId));
	EXPECT_CALL(helper, toJstring(StrCaseEq("foobar")))
		.Times(1)
		.WillOnce(Return(jmessage));
	EXPECT_CALL(helper, createObject_LLDS(
			StrCaseEq("ru/prolib/JWQuik/Driver$TransactionResult"),
			StrCaseEq("(JJDLjava/lang/String;)V"),
			800, 100500, 33.44, jmessage))
		.Times(1)
		.WillOnce(Return(jtr));
	EXPECT_CALL(helper, callVoidMethod_LLO(callback,
			onTransactionReplyId, 3, 235, jtr))
		.Times(1);
	EXPECT_CALL(helper, drop())
		.Times(1)
		.WillOnce(Return(true));

	DriverCallbackTransfer transfer(&helper, &driver, obj);
	transfer.onTransactionReply(result, errorCode, &tr);

	EXPECT_DESTRUCTOR_CALLS();
}

TEST_F(DriverCallbackTransferTest, testOnOrderStatus) {
	JavaVM* jvm = (JavaVM*)FAKE_JVM_PTR;
	jobject callback = (jobject)1111;
	jmethodID onOrderStatusId = (jmethodID)2222;
	jobject jorder = (jobject)3333;
	long mode = 1;

	EXPECT_CONSTRUCTOR_CALLS();
	EXPECT_CALL(strategy, produce(jvm))
		.Times(1)
		.WillOnce(Return(&helper));
	EXPECT_CALL(helper, getObjectField((jobject)FAKE_OBJ_PTR,
			StrCaseEq("callback"),
			StrCaseEq("Lru/prolib/JWQuik/ICallback;")))
		.Times(1)
		.WillOnce(Return(callback));
	EXPECT_CALL(helper, getMethodId(callback,
			StrCaseEq("onOrderStatus"),
			StrCaseEq("(JLru/prolib/JWQuik/IOrder;)V")))
		.Times(1)
		.WillOnce(Return(onOrderStatusId));
	EXPECT_CALL(helper, createObject_L(
			StrCaseEq("ru/prolib/JWQuik/Driver$Order"),
			StrCaseEq("(J)V"),
			(jlong)&order))
		.Times(1)
		.WillOnce(Return(jorder));
	EXPECT_CALL(helper, callVoidMethod_LO
			(callback, onOrderStatusId, (jlong)mode, jorder))
		.Times(1);
	EXPECT_CALL(helper, drop())
		.Times(1)
		.WillOnce(Return(true));

	DriverCallbackTransfer transfer(&helper, &driver, obj);
	transfer.onOrderStatus(mode, &order);

	EXPECT_DESTRUCTOR_CALLS();
}

TEST_F(DriverCallbackTransferTest, testOnTradeStatus) {
	JavaVM* jvm = (JavaVM*)FAKE_JVM_PTR;
	jobject callback = (jobject)1111;
	jmethodID onTradeStatusId = (jmethodID)2222;
	jobject jtrade = (jobject)3333;
	long mode = 1;

	EXPECT_CONSTRUCTOR_CALLS();
	EXPECT_CALL(strategy, produce(jvm))
		.Times(1)
		.WillOnce(Return(&helper));
	EXPECT_CALL(helper, getObjectField((jobject)FAKE_OBJ_PTR,
			StrCaseEq("callback"),
			StrCaseEq("Lru/prolib/JWQuik/ICallback;")))
		.Times(1)
		.WillOnce(Return(callback));
	EXPECT_CALL(helper, getMethodId(callback,
			StrCaseEq("onTradeStatus"),
			StrCaseEq("(JLru/prolib/JWQuik/ITrade;)V")))
		.Times(1)
		.WillOnce(Return(onTradeStatusId));
	EXPECT_CALL(helper, createObject_L(
			StrCaseEq("ru/prolib/JWQuik/Driver$Trade"),
			StrCaseEq("(J)V"),
			(jlong)&trade))
		.Times(1)
		.WillOnce(Return(jtrade));
	EXPECT_CALL(helper, callVoidMethod_LO
			(callback, onTradeStatusId, (jlong)mode, jtrade))
		.Times(1);
	EXPECT_CALL(helper, drop())
		.Times(1)
		.WillOnce(Return(true));

	DriverCallbackTransfer transfer(&helper, &driver, obj);
	transfer.onTradeStatus(mode, &trade);

	EXPECT_DESTRUCTOR_CALLS();
}
