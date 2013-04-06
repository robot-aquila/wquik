#include <jni.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string.h>
#include "helper.h"
#include "jwquik/JWQuik.h"
#include "MockOrder.h"
#include "TestEnv.h"

#define JWQUIK_ORDER_CONSTRUCTOR		"<init>"
#define JWQUIK_ORDER_CONSTRUCTOR_SIG	"(J)V"

#define JWQUIK_ORDER_TEST_GETTER_D(method, retval) \
	JWQUIK_TEST_GETTER_D(JavaOrderTest, order, method, retval);

#define JWQUIK_ORDER_TEST_GETTER_L(method, retval) \
	JWQUIK_TEST_GETTER_L(JavaOrderTest, order, method, retval);

#define JWQUIK_ORDER_TEST_GETTER_S(method, retval) \
	JWQUIK_TEST_GETTER_S(JavaOrderTest, order, method, retval);

#define JWQUIK_ORDER_TEST_GETTER_B(method, retval) \
	JWQUIK_TEST_GETTER_B(JavaOrderTest, order, method, retval);


using namespace testing;
using namespace wquik;

class JavaOrderTest : public ::testing::Test {
public:
	MockOrder order;
	static JNIEnv *env;
	static jclass classId;
	static jmethodID constructorId;
	static jfieldID descriptorId;

	static void SetUpTestCase() {
		env = TestEnv::getEnv();
		classId = env->FindClass(JWQUIK_ORDER_CLASS);
		if ( classId == NULL ) {
			FAIL() << "Class " << JWQUIK_ORDER_CLASS << " not found\n";
		}
		constructorId = env->GetMethodID
			(classId, JWQUIK_ORDER_CONSTRUCTOR, JWQUIK_ORDER_CONSTRUCTOR_SIG);
		if ( constructorId == NULL ) {
			FAIL() << "Constructor method ID not found\n";
		}
		descriptorId = env->GetFieldID(classId, JWQUIK_ORDER_DESCRIPTOR_FIELD,
			JWQUIK_ORDER_DESCRIPTOR_SIG);
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
		EXPECT_CALL(order, grab())
			.Times(1)
			.WillOnce(Return(&order));
	}

};

JNIEnv* JavaOrderTest::env = 0;
jclass JavaOrderTest::classId = 0;
jmethodID JavaOrderTest::constructorId = 0;
jfieldID JavaOrderTest::descriptorId = 0;

TEST_F(JavaOrderTest, testConstruct) {
	EXPECT_CONSTRUCTOR_CALLS();

	jobject obj = env->NewObject(classId, constructorId, (jlong)&order);
	jlong descr = env->GetLongField(obj, descriptorId);
	ASSERT_EQ((jlong)&order, descr);
}

TEST_F(JavaOrderTest, testRelease) {
	EXPECT_CONSTRUCTOR_CALLS();
	EXPECT_CALL(order, drop())
		.Times(1)
		.WillOnce(Return(true));

	jobject obj = env->NewObject(classId, constructorId, (jlong)&order);
	jmethodID m = env->GetMethodID(classId, "free", "()V");
	env->CallVoidMethod(obj, m);
	jlong descr = env->GetLongField(obj, descriptorId);
	ASSERT_EQ(0, descr);
}

JWQUIK_ORDER_TEST_GETTER_L(getQty, 2001);
JWQUIK_ORDER_TEST_GETTER_L(getDate, 1111);
JWQUIK_ORDER_TEST_GETTER_L(getTime, 8888);
JWQUIK_ORDER_TEST_GETTER_L(getActivationTime, 9999);
JWQUIK_ORDER_TEST_GETTER_L(getWithdrawTime, 7777);
JWQUIK_ORDER_TEST_GETTER_L(getExpiry, 6666);
JWQUIK_ORDER_TEST_GETTER_D(getAccruedInt, 2222.11);
JWQUIK_ORDER_TEST_GETTER_D(getYield, 32222.11);
JWQUIK_ORDER_TEST_GETTER_L(getUID, 777);
JWQUIK_ORDER_TEST_GETTER_S(getUserId, "USER ID");
JWQUIK_ORDER_TEST_GETTER_S(getAccount, "ACCOUNT");
JWQUIK_ORDER_TEST_GETTER_S(getBrokerRef, "BROKER");
JWQUIK_ORDER_TEST_GETTER_S(getClientCode, "ZZZZ");
JWQUIK_ORDER_TEST_GETTER_S(getFirmId, "FIRM");
JWQUIK_ORDER_TEST_GETTER_L(getTransId, 888);
JWQUIK_ORDER_TEST_GETTER_D(getNumber, 777.22);
JWQUIK_ORDER_TEST_GETTER_S(getClassCode, "EQBR");
JWQUIK_ORDER_TEST_GETTER_S(getSecCode, "GAZP");
JWQUIK_ORDER_TEST_GETTER_D(getPrice, 111.444);
JWQUIK_ORDER_TEST_GETTER_L(getBalance, 123456);
JWQUIK_ORDER_TEST_GETTER_D(getValue, 11.22);
JWQUIK_ORDER_TEST_GETTER_B(isSell, true);
JWQUIK_ORDER_TEST_GETTER_L(getStatus, 5);

