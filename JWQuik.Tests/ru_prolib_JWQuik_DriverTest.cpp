#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "MockJavaHelper.h"
#include "MockTransactionDriver.h"
#include "MockWrapperStrategy.h"
#include "MockDriverCallbackTransfer.h"
#include "jwquik/ru_prolib_JWQuik_Driver.h"

using namespace testing;
using namespace wquik;

#define FAKE_JVM_PTR 778899
#define FAKE_OBJ_PTR 992233
#define FAKE_ENV_PTR 112233

class JavaDriverTest : public ::testing::Test {
public:
	MockJavaHelper helper;
	MockTransactionDriver driver;
	MockWrapperStrategy strategy;
	MockDriverCallbackTransfer transfer;
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

	void sendSyncTransaction(const char* str, TransactionResult *tr);

};

TEST_F(JavaDriverTest, testInit_J) {
	EXPECT_CALL(strategy, produce((JNIEnv*)FAKE_ENV_PTR))
		.Times(1)
		.WillOnce(Return(&helper));
	// calleb by DriverCallbackTransfer constructor
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
	//
	EXPECT_CALL(helper, setLongField(obj,
			StrCaseEq("descriptor"),
			StrCaseEq("J"), _))
		.Times(1);
	EXPECT_CALL(helper, drop())
		.Times(1)
		.WillOnce(Return(true));

	Java_ru_prolib_JWQuik_Driver_init__J((JNIEnv*)FAKE_ENV_PTR, obj,
		(jlong)&driver);
}

TEST_F(JavaDriverTest, testRelease) {
	EXPECT_CALL(strategy, produce((JNIEnv*)FAKE_ENV_PTR))
		.Times(1)
		.WillOnce(Return(&helper));
	EXPECT_CALL(helper, getLongField(obj,
			StrCaseEq("descriptor"), StrCaseEq("J")))
		.Times(1)
		.WillOnce(Return((jlong)&transfer));
	EXPECT_CALL(transfer, drop())
		.Times(1)
		.WillOnce(Return(true));
	EXPECT_CALL(helper, setLongField(obj,
			StrCaseEq("descriptor"), StrCaseEq("J"), 0))
		.Times(1);
	EXPECT_CALL(helper, drop())
		.Times(1)
		.WillOnce(Return(true));

	Java_ru_prolib_JWQuik_Driver_release((JNIEnv*)FAKE_ENV_PTR, obj);
}

TEST_F(JavaDriverTest, testSetAsyncMode) {
	EXPECT_CALL(strategy, produce((JNIEnv*)FAKE_ENV_PTR))
		.Times(1)
		.WillOnce(Return(&helper));
	EXPECT_CALL(helper, getLongField(obj,
			StrCaseEq("descriptor"), StrCaseEq("J")))
		.Times(1)
		.WillOnce(Return((jlong)&transfer));
	EXPECT_CALL(transfer, getDriver())
		.Times(1)
		.WillOnce(Return(&driver));
	EXPECT_CALL(driver, setAsyncMode())
		.Times(1);
	EXPECT_CALL(helper, drop())
		.Times(1)
		.WillOnce(Return(true));

	Java_ru_prolib_JWQuik_Driver_setAsyncMode((JNIEnv*)FAKE_ENV_PTR, obj);
}

TEST_F(JavaDriverTest, testSetSyncMode) {
	EXPECT_CALL(strategy, produce((JNIEnv*)FAKE_ENV_PTR))
		.Times(1)
		.WillOnce(Return(&helper));
	EXPECT_CALL(helper, getLongField(obj,
			StrCaseEq("descriptor"), StrCaseEq("J")))
		.Times(1)
		.WillOnce(Return((jlong)&transfer));
	EXPECT_CALL(transfer, getDriver())
		.Times(1)
		.WillOnce(Return(&driver));
	EXPECT_CALL(driver, setSyncMode())
		.Times(1);
	EXPECT_CALL(helper, drop())
		.Times(1)
		.WillOnce(Return(true));

	Java_ru_prolib_JWQuik_Driver_setSyncMode((JNIEnv*)FAKE_ENV_PTR, obj);
}

TEST_F(JavaDriverTest, testIsSyncMode) {
	EXPECT_CALL(strategy, produce((JNIEnv*)FAKE_ENV_PTR))
		.Times(1)
		.WillOnce(Return(&helper));
	EXPECT_CALL(helper, getLongField(obj,
			StrCaseEq("descriptor"), StrCaseEq("J")))
		.Times(1)
		.WillOnce(Return((jlong)&transfer));
	EXPECT_CALL(transfer, getDriver())
		.Times(1)
		.WillOnce(Return(&driver));
	EXPECT_CALL(driver, isSyncMode())
		.Times(1)
		.WillOnce(Return(true));
	EXPECT_CALL(helper, drop())
		.Times(1)
		.WillOnce(Return(true));

	ASSERT_EQ(JNI_TRUE,
		Java_ru_prolib_JWQuik_Driver_isSyncMode((JNIEnv*)FAKE_ENV_PTR, obj));
}

TEST_F(JavaDriverTest, testIsAyncMode) {
	EXPECT_CALL(strategy, produce((JNIEnv*)FAKE_ENV_PTR))
		.Times(1)
		.WillOnce(Return(&helper));
	EXPECT_CALL(helper, getLongField(obj,
			StrCaseEq("descriptor"), StrCaseEq("J")))
		.Times(1)
		.WillOnce(Return((jlong)&transfer));
	EXPECT_CALL(transfer, getDriver())
		.Times(1)
		.WillOnce(Return(&driver));
	EXPECT_CALL(driver, isAsyncMode())
		.Times(1)
		.WillOnce(Return(true));
	EXPECT_CALL(helper, drop())
		.Times(1)
		.WillOnce(Return(true));

	ASSERT_EQ(JNI_TRUE,
		Java_ru_prolib_JWQuik_Driver_isAsyncMode((JNIEnv*)FAKE_ENV_PTR, obj));
}

TEST_F(JavaDriverTest, testConnect) {
	jstring jstr = (jstring)56789;
	EXPECT_CALL(strategy, produce((JNIEnv*)FAKE_ENV_PTR))
		.Times(1)
		.WillOnce(Return(&helper));
	EXPECT_CALL(helper, getLongField(obj,
			StrCaseEq("descriptor"), StrCaseEq("J")))
		.Times(1)
		.WillOnce(Return((jlong)&transfer));
	EXPECT_CALL(transfer, getDriver())
		.Times(1)
		.WillOnce(Return(&driver));
	EXPECT_CALL(helper, toString(jstr))
		.Times(1)
		.WillOnce(Return((string)"path/to/quik"));
	EXPECT_CALL(driver, connect(StrCaseEq("path/to/quik")))
		.Times(1);
	EXPECT_CALL(helper, drop())
		.Times(1)
		.WillOnce(Return(true));

	Java_ru_prolib_JWQuik_Driver_connect((JNIEnv*)FAKE_ENV_PTR, obj, jstr);
}

TEST_F(JavaDriverTest, testDisconnect) {
	EXPECT_CALL(strategy, produce((JNIEnv*)FAKE_ENV_PTR))
		.Times(1)
		.WillOnce(Return(&helper));
	EXPECT_CALL(helper, getLongField(obj,
			StrCaseEq("descriptor"), StrCaseEq("J")))
		.Times(1)
		.WillOnce(Return((jlong)&transfer));
	EXPECT_CALL(transfer, getDriver())
		.Times(1)
		.WillOnce(Return(&driver));
	EXPECT_CALL(driver, disconnect())
		.Times(1);
	EXPECT_CALL(helper, drop())
		.Times(1)
		.WillOnce(Return(true));

	Java_ru_prolib_JWQuik_Driver_disconnect((JNIEnv*)FAKE_ENV_PTR, obj);
}

TEST_F(JavaDriverTest, testIsDllConnected) {
	EXPECT_CALL(strategy, produce((JNIEnv*)FAKE_ENV_PTR))
		.Times(1)
		.WillOnce(Return(&helper));
	EXPECT_CALL(helper, getLongField(obj,
			StrCaseEq("descriptor"), StrCaseEq("J")))
		.Times(1)
		.WillOnce(Return((jlong)&transfer));
	EXPECT_CALL(transfer, getDriver())
		.Times(1)
		.WillOnce(Return(&driver));
	EXPECT_CALL(driver, isDllConnected())
		.Times(1)
		.WillOnce(Return(true));
	EXPECT_CALL(helper, drop())
		.Times(1)
		.WillOnce(Return(true));

	ASSERT_EQ(JNI_TRUE, Java_ru_prolib_JWQuik_Driver_isDllConnected
		((JNIEnv*)FAKE_ENV_PTR, obj));
}

TEST_F(JavaDriverTest, testIsQuikConnected) {
	EXPECT_CALL(strategy, produce((JNIEnv*)FAKE_ENV_PTR))
		.Times(1)
		.WillOnce(Return(&helper));
	EXPECT_CALL(helper, getLongField(obj,
			StrCaseEq("descriptor"), StrCaseEq("J")))
		.Times(1)
		.WillOnce(Return((jlong)&transfer));
	EXPECT_CALL(transfer, getDriver())
		.Times(1)
		.WillOnce(Return(&driver));
	EXPECT_CALL(driver, isQuikConnected())
		.Times(1)
		.WillOnce(Return(true));
	EXPECT_CALL(helper, drop())
		.Times(1)
		.WillOnce(Return(true));

	ASSERT_EQ(JNI_TRUE, Java_ru_prolib_JWQuik_Driver_isQuikConnected
		((JNIEnv*)FAKE_ENV_PTR, obj));
}

void JavaDriverTest::sendSyncTransaction(const char* str,
										 TransactionResult *tr)
{
	tr->replyCode = 3;
	tr->transId = 800;
	tr->orderNumber = 33.44;
	tr->resultMessage = "foobar";
}

TEST_F(JavaDriverTest, testSendSyncTransaction) {
	jstring jstr = (jstring)777666;
	jstring jmsg = (jstring)555444;
	jobject jtr = (jobject)111111;

	EXPECT_CALL(strategy, produce((JNIEnv*)FAKE_ENV_PTR))
		.Times(1)
		.WillOnce(Return(&helper));
	EXPECT_CALL(helper, getLongField(obj,
			StrCaseEq("descriptor"), StrCaseEq("J")))
		.Times(1)
		.WillOnce(Return((jlong)&transfer));
	EXPECT_CALL(transfer, getDriver())
		.Times(1)
		.WillOnce(Return(&driver));
	EXPECT_CALL(helper, toString(jstr))
		.Times(1)
		.WillOnce(Return((string)"jubba-bubba"));
	EXPECT_CALL(driver, sendSyncTransaction(StrCaseEq("jubba-bubba"), _))
		.Times(1)
		.WillOnce(Invoke(this, &JavaDriverTest::sendSyncTransaction));
	EXPECT_CALL(helper, toJstring(StrCaseEq("foobar")))
		.Times(1)
		.WillOnce(Return(jmsg));
	EXPECT_CALL(helper, createObject_LLDS(
			StrCaseEq("ru/prolib/JWQuik/Driver$TransactionResult"),
			StrCaseEq("(JJDLjava/lang/String;)V"),
			(jlong)3, (jlong)800, (jdouble)33.44, jmsg))
		.Times(1)
		.WillOnce(Return(jtr));
	EXPECT_CALL(helper, drop())
		.Times(1)
		.WillOnce(Return(true));

	ASSERT_EQ(jtr, Java_ru_prolib_JWQuik_Driver_sendSyncTransaction
		((JNIEnv*)FAKE_ENV_PTR, obj, jstr));
}

TEST_F(JavaDriverTest, testSendAsyncTransaction) {
	jstring jstr = (jstring)777666;

	EXPECT_CALL(strategy, produce((JNIEnv*)FAKE_ENV_PTR))
		.Times(1)
		.WillOnce(Return(&helper));
	EXPECT_CALL(helper, getLongField(obj,
			StrCaseEq("descriptor"), StrCaseEq("J")))
		.Times(1)
		.WillOnce(Return((jlong)&transfer));
	EXPECT_CALL(transfer, getDriver())
		.Times(1)
		.WillOnce(Return(&driver));
	EXPECT_CALL(helper, toString(jstr))
		.Times(1)
		.WillOnce(Return((string)"jubba-bubba"));
	EXPECT_CALL(driver, sendAsyncTransaction(StrCaseEq("jubba-bubba")))
		.Times(1);
	EXPECT_CALL(helper, drop())
		.Times(1)
		.WillOnce(Return(true));

	Java_ru_prolib_JWQuik_Driver_sendAsyncTransaction((JNIEnv*)FAKE_ENV_PTR,
		obj, jstr);
}
