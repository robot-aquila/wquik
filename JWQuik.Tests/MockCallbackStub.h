#pragma once
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "jwquik/JWQuik.h"

using namespace jwquik;

class MockCallbackStub : public ICallbackStub {
public:
	virtual ~MockCallbackStub(void){};

	MOCK_METHOD5(onConnectionStatus, void(JNIEnv *, jobject, jlong, jlong, jstring));
	MOCK_METHOD4(onOrderStatus, void(JNIEnv *, jobject, jlong, jobject));
	MOCK_METHOD4(onTradeStatus, void(JNIEnv *, jobject, jlong, jobject));
	MOCK_METHOD5(onTransactionReply, void(JNIEnv *, jobject, jlong, jlong, jobject));
};
