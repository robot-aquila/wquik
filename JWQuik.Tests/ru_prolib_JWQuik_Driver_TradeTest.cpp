#include <jni.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string.h>
#include "helper.h"
#include "jwquik/JWQuik.h"
#include "MockTrade.h"
#include "TestEnv.h"

#define JWQUIK_TRADE_CONSTRUCTOR		"<init>"
#define JWQUIK_TRADE_CONSTRUCTOR_SIG	"(J)V"

#define JWQUIK_TRADE_TEST_GETTER_D(method, retval) \
	JWQUIK_TEST_GETTER_D(JavaTradeTest, trade, method, retval);

#define JWQUIK_TRADE_TEST_GETTER_L(method, retval) \
	JWQUIK_TEST_GETTER_L(JavaTradeTest, trade, method, retval);

#define JWQUIK_TRADE_TEST_GETTER_S(method, retval) \
	JWQUIK_TEST_GETTER_S(JavaTradeTest, trade, method, retval);

#define JWQUIK_TRADE_TEST_GETTER_B(method, retval) \
	JWQUIK_TEST_GETTER_B(JavaTradeTest, trade, method, retval);

using namespace testing;
using namespace wquik;

class JavaTradeTest : public ::testing::Test {
public:
	MockTrade trade;
	static jclass classId;
	static jmethodID constructorId;
	static jfieldID descriptorId;
	static JNIEnv* env;

	static void SetUpTestCase() {
		env = TestEnv::getEnv();
		classId = env->FindClass(JWQUIK_TRADE_CLASS);
		if ( classId == NULL ) {
			FAIL() << "Class " << JWQUIK_TRADE_CLASS << " not found\n";
		}
		constructorId = env->GetMethodID
			(classId, JWQUIK_TRADE_CONSTRUCTOR, JWQUIK_TRADE_CONSTRUCTOR_SIG);
		if ( constructorId == NULL ) {
			FAIL() << "Constructor method ID not found\n";
		}
		descriptorId = env->GetFieldID(classId, JWQUIK_TRADE_DESCRIPTOR_FIELD,
			JWQUIK_TRADE_DESCRIPTOR_SIG);
		if ( descriptorId == NULL ) {
			FAIL() << "Descriptor field ID not found\n";
		}
	}

	static void TearDownTestCase() {
	}

	virtual void SetUp() {
	}

	virtual void TearDown() {
	}

	void EXPECT_CONSTRUCTOR_CALLS() {
		EXPECT_CALL(trade, grab())
			.Times(1)
			.WillOnce(Return(&trade));
	}

};

JNIEnv* JavaTradeTest::env = 0;
jclass JavaTradeTest::classId = 0;
jmethodID JavaTradeTest::constructorId = 0;
jfieldID JavaTradeTest::descriptorId = 0;

TEST_F(JavaTradeTest, testConstruct) {
	EXPECT_CONSTRUCTOR_CALLS();

	jobject obj = env->NewObject(classId, constructorId, (jlong)&trade);
	jlong descr = env->GetLongField(obj, descriptorId);
	ASSERT_EQ((jlong)&trade, descr);
}

TEST_F(JavaTradeTest, testRelease) {
	EXPECT_CONSTRUCTOR_CALLS();
	EXPECT_CALL(trade, drop())
		.Times(1)
		.WillOnce(Return(true));

	jobject obj = env->NewObject(classId, constructorId, (jlong)&trade);
	jmethodID m = env->GetMethodID(classId, "free", "()V");
	env->CallVoidMethod(obj, m);
	jlong descr = env->GetLongField(obj, descriptorId);
	ASSERT_EQ(0, descr);
}

JWQUIK_TRADE_TEST_GETTER_L(getDate, 2001);
JWQUIK_TRADE_TEST_GETTER_L(getSettleDate, 1002);
JWQUIK_TRADE_TEST_GETTER_L(getTime, 11112222);
JWQUIK_TRADE_TEST_GETTER_B(isMarginal, true);
JWQUIK_TRADE_TEST_GETTER_D(getAccruedInt, 12.12);
JWQUIK_TRADE_TEST_GETTER_D(getYield, 1112.2212);
JWQUIK_TRADE_TEST_GETTER_D(getTsCommission, 88.77);
JWQUIK_TRADE_TEST_GETTER_D(getClearingCenterCommission, 11.44);
JWQUIK_TRADE_TEST_GETTER_D(getExchangeCommission, 66.55);
JWQUIK_TRADE_TEST_GETTER_D(getTradingSystemCommission, 99.11);
JWQUIK_TRADE_TEST_GETTER_D(getPrice2, 22212.12121);
JWQUIK_TRADE_TEST_GETTER_D(getRepoRate, 888.222);
JWQUIK_TRADE_TEST_GETTER_D(getRepoValue, 777.22);
JWQUIK_TRADE_TEST_GETTER_D(getRepo2Value, 66.55);
JWQUIK_TRADE_TEST_GETTER_D(getAccruedInt2, 12345.22);
JWQUIK_TRADE_TEST_GETTER_L(getRepoTerm, 999888777);
JWQUIK_TRADE_TEST_GETTER_D(getStartDiscount, 345.345);
JWQUIK_TRADE_TEST_GETTER_D(getLowerDiscount, 6611.255);
JWQUIK_TRADE_TEST_GETTER_D(getUpperDiscount, 123.123);
JWQUIK_TRADE_TEST_GETTER_L(getBlockSecurities, 1111);
JWQUIK_TRADE_TEST_GETTER_S(getCurrency, "ZUKAZUKA");
JWQUIK_TRADE_TEST_GETTER_S(getSettleCurrency, "RUR");
JWQUIK_TRADE_TEST_GETTER_S(getSettleCode, "ZBR");
JWQUIK_TRADE_TEST_GETTER_S(getAccount, "ACCOUNT");
JWQUIK_TRADE_TEST_GETTER_S(getBrokerRef, "BROKER");
JWQUIK_TRADE_TEST_GETTER_S(getClientCode, "CLIENT");
JWQUIK_TRADE_TEST_GETTER_S(getUserId, "USER");
JWQUIK_TRADE_TEST_GETTER_S(getFirmId, "FIRM");
JWQUIK_TRADE_TEST_GETTER_S(getPartnerFirmId, "PARTNER");
JWQUIK_TRADE_TEST_GETTER_S(getExchangeCode, "EX");
JWQUIK_TRADE_TEST_GETTER_S(getStationId, "STATION");
JWQUIK_TRADE_TEST_GETTER_D(getNumber, 876.543);
JWQUIK_TRADE_TEST_GETTER_D(getOrderNumber, 123.456);
JWQUIK_TRADE_TEST_GETTER_S(getClassCode, "EQBR");
JWQUIK_TRADE_TEST_GETTER_S(getSecCode, "SBER");
JWQUIK_TRADE_TEST_GETTER_D(getPrice, 22.3344);
JWQUIK_TRADE_TEST_GETTER_L(getQty, 100000);
JWQUIK_TRADE_TEST_GETTER_B(isSell, false);
JWQUIK_TRADE_TEST_GETTER_D(getValue, 987.654);
