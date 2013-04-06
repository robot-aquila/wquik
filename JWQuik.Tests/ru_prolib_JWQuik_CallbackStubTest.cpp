#include <jni.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string.h>
#include "helper.h"
#include "jwquik/JWQuik.h"
#include "MockOrder.h"
#include "MockTrade.h"
#include "MockCallbackStub.h"
#include "TestEnv.h"

#define JWQUIK_CBSTUB_CONSTRUCTOR		"<init>"
#define JWQUIK_CBSTUB_CONSTRUCTOR_SIG	"(J)V"

using namespace testing;
using namespace wquik;

class JavaCallbackStubTest : public ::testing::Test {
public:
	MockOrder order;
	MockTrade trade;
	MockCallbackStub callbackStub;
	jobject obj,arg;
	static JNIEnv *env;
	static jclass classId;
	static jmethodID constructorId;
	static jfieldID descriptorId;

	static void SetUpTestCase() {
		env = TestEnv::getEnv();
		classId = env->FindClass(JWQUIK_CBSTUB_CLASS);
		if ( classId == NULL ) {
			FAIL() << "Class " << JWQUIK_CBSTUB_CLASS << " not found\n";
		}
		constructorId = env->GetMethodID
			(classId, JWQUIK_CBSTUB_CONSTRUCTOR, JWQUIK_CBSTUB_CONSTRUCTOR_SIG);
		if ( constructorId == NULL ) {
			FAIL() << "Constructor method ID not found\n";
		}
		descriptorId = env->GetFieldID(classId, JWQUIK_CBSTUB_DESCRIPTOR_FIELD,
			JWQUIK_CBSTUB_DESCRIPTOR_SIG);
		if ( descriptorId == NULL ) {
			FAIL() << "Descriptor field ID not found\n";
		}		
	}

	static void TearDownTestCase() {
	}

	virtual void SetUp() {
		obj = env->NewObject(classId, constructorId, (jlong)&callbackStub);
	}

	virtual void TearDown() {
	}

	void EXPECT_CONSTRUCTOR_CALLS() {
	}

	void check_onConnectionStatus(JNIEnv * env, jobject o, jlong e, jlong err, jobject m);
	void check_onOrderStatus(JNIEnv * env, jobject o, jlong mode, jobject o2);
	void check_onTradeStatus(JNIEnv * env, jobject o, jlong mode, jobject o2);
	void check_onTransactionReply
		(JNIEnv * env, jobject o, jlong result, jlong errCode, jobject o2);
};

JNIEnv* JavaCallbackStubTest::env = 0;
jclass JavaCallbackStubTest::classId = 0;
jmethodID JavaCallbackStubTest::constructorId = 0;
jfieldID JavaCallbackStubTest::descriptorId = 0;

void JavaCallbackStubTest::check_onConnectionStatus
	(JNIEnv * env, jobject o, jlong eid, jlong err, jobject m)
{
	ASSERT_JBOOL(true, env->IsSameObject(obj, o));
	ASSERT_JSTREQ("HELLO", (jstring)m);
}

TEST_F(JavaCallbackStubTest, testOnConnectionStatus) {
	jmethodID m = env->GetMethodID(classId, "onConnectionStatus", "(JJLjava/lang/String;)V");
	jstring msg = env->NewString((const jchar*)L"HELLO", 5);

	EXPECT_CALL(callbackStub,
			onConnectionStatus(env, _, (jlong)12, (jlong)15, _))
		.Times(1)
		.WillOnce(Invoke(this, &JavaCallbackStubTest::check_onConnectionStatus));

	env->CallVoidMethod(obj, m, (jlong)12, (jlong)15, msg);
}

void JavaCallbackStubTest::check_onOrderStatus
	(JNIEnv * env, jobject o, jlong mode, jobject o2)
{
	ASSERT_JBOOL(true, env->IsSameObject(obj, o));
	ASSERT_JBOOL(true, env->IsSameObject(arg, o2));
}

TEST_F(JavaCallbackStubTest, testOnOrderStatus) {
	EXPECT_CALL(order, grab())
		.Times(1)
		.WillOnce(Return(&order));
	EXPECT_CALL(callbackStub,
			onOrderStatus(env, _, (jlong)123, _))
		.Times(1)
		.WillOnce(Invoke(this, &JavaCallbackStubTest::check_onOrderStatus));

	jclass orderClass = env->FindClass(JWQUIK_ORDER_CLASS);
	ASSERT_NE((jclass)NULL, orderClass);
	jmethodID orderConstructorId = env->GetMethodID(orderClass, "<init>", "(J)V");
	ASSERT_NE((jmethodID)NULL, orderConstructorId);
	arg = env->NewObject(orderClass, orderConstructorId, (jlong)&order);
	ASSERT_NE((jobject)NULL, arg);
	jmethodID m = env->GetMethodID(classId, "onOrderStatus", "(JLru/prolib/JWQuik/IOrder;)V");
	env->CallVoidMethod(obj, m, (jlong)123, (jobject)arg);
}

void JavaCallbackStubTest::check_onTradeStatus
	(JNIEnv * env, jobject o, jlong mode, jobject o2)
{
	ASSERT_JBOOL(true, env->IsSameObject(obj, o));
	ASSERT_JBOOL(true, env->IsSameObject(arg, o2));
}

TEST_F(JavaCallbackStubTest, testOnTradeStatus) {
	EXPECT_CALL(trade, grab())
		.Times(1)
		.WillOnce(Return(&trade));
	EXPECT_CALL(callbackStub,
			onTradeStatus(env, _, (jlong)123, _))
		.Times(1)
		.WillOnce(Invoke(this, &JavaCallbackStubTest::check_onTradeStatus));

	jclass tradeClass = env->FindClass(JWQUIK_TRADE_CLASS);
	ASSERT_NE((jclass)NULL, tradeClass);
	jmethodID tradeConstructorId = env->GetMethodID(tradeClass, "<init>", "(J)V");
	ASSERT_NE((jmethodID)NULL, tradeConstructorId);
	arg = env->NewObject(tradeClass, tradeConstructorId, (jlong)&trade);
	ASSERT_NE((jobject)NULL, arg);
	jmethodID m = env->GetMethodID(classId, "onTradeStatus", "(JLru/prolib/JWQuik/ITrade;)V");
	env->CallVoidMethod(obj, m, (jlong)123, (jobject)arg);
}

void JavaCallbackStubTest::check_onTransactionReply
	(JNIEnv * env, jobject o, jlong result, jlong errCode, jobject o2)
{
	ASSERT_JBOOL(true, env->IsSameObject(obj, o));
	ASSERT_JBOOL(true, env->IsSameObject(arg, o2));
}

TEST_F(JavaCallbackStubTest, testOnTransactionReply) {
	EXPECT_CALL(callbackStub,
			onTransactionReply(env, _, (jlong)123, (jlong)321, _))
		.Times(1)
		.WillOnce(Invoke(this,
			&JavaCallbackStubTest::check_onTransactionReply));

	jclass trClass = env->FindClass
		("ru/prolib/JWQuik/Driver$TransactionResult");
	ASSERT_NE((jclass)NULL, trClass);
	jmethodID trConstructorId = env->GetMethodID
		(trClass, "<init>", "(JJDLjava/lang/String;)V");
	ASSERT_NE((jmethodID)NULL, trConstructorId);
	jstring msg = env->NewString((const jchar*)L"ZZZ", 3);
	ASSERT_NE((jstring)NULL, msg);
	arg = env->NewObject
		(trClass, trConstructorId, (jlong)1, (jlong)2, (jdouble)1.2, msg);
	ASSERT_NE((jobject)NULL, arg);
	jmethodID m = env->GetMethodID(classId, "onTransactionReply",
		"(JJLru/prolib/JWQuik/ITransactionResult;)V");
	env->CallVoidMethod(obj, m, (jlong)123, (jlong)321, arg);
}
