#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <jwquik/JavaWrapper.h>
#include "MockWrapperStrategy.h"

using namespace testing;

class JavaWrapperTest : public ::testing::Test {
public:
	MockWrapperStrategy strategy;

	virtual void SetUp() {
		//if ( JavaWrapper::getStrategy() != &strategy ) {
		//	EXPECT_CALL(strategy, drop())
		//		.Times(1)
		//		.WillOnce(Return(true));
		//	JavaWrapper::setStrategy(&strategy);
		//}
	}

	virtual void TearDown() {
		//EXPECT_CALL(strategy, drop())
		//	.Times(1)
		//	.WillOnce(Return(true));
		JavaWrapper::setStrategy(0);
	}
};

TEST_F(JavaWrapperTest, testSetStrategyDropsPrevious) {
	EXPECT_CALL(strategy, grab())
		.Times(1)
		.WillOnce(Return(&strategy));
	EXPECT_CALL(strategy, drop())
		.Times(1)
		.WillOnce(Return(true));

	JavaWrapper::setStrategy(&strategy);
	JavaWrapper::setStrategy(0);
}

TEST_F(JavaWrapperTest, testGetStrategyReturnsDefault) {
	ASSERT_NE((IWrapperStrategy*)0, JavaWrapper::getStrategy());
}

TEST_F(JavaWrapperTest, testWrapJNIEnv) {
	JNIEnv* env = (JNIEnv*)12345;
	IJavaHelper* helper = (IJavaHelper*)54321;

	EXPECT_CALL(strategy, grab())
		.Times(1)
		.WillOnce(Return(&strategy));
	EXPECT_CALL(strategy, produce(env))
		.Times(1)
		.WillOnce(Return(helper));
	EXPECT_CALL(strategy, drop())
		.Times(1)
		.WillOnce(Return(true));

	JavaWrapper::setStrategy(&strategy);
	ASSERT_EQ(helper, JavaWrapper::wrap(env));

	JavaWrapper::setStrategy(0);
}

TEST_F(JavaWrapperTest, testWrapJavaVM) {
	JavaVM* jvm = (JavaVM*)8888;
	IJavaHelper* helper = (IJavaHelper*)9999;

	EXPECT_CALL(strategy, grab())
		.Times(1)
		.WillOnce(Return(&strategy));
	EXPECT_CALL(strategy, drop())
		.Times(1)
		.WillOnce(Return(true));
	EXPECT_CALL(strategy, produce(jvm))
		.Times(1)
		.WillOnce(Return(helper));

	JavaWrapper::setStrategy(&strategy);
	ASSERT_EQ(helper, JavaWrapper::wrap(jvm));

	JavaWrapper::setStrategy(0);
}
