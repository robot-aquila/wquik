#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "jwquik/JavaWrapper.h"

using namespace jwquik;

class MockJavaHelper : public IJavaHelper {
public:
	virtual ~MockJavaHelper(void){};

	MOCK_METHOD0(grab, void*());
	MOCK_METHOD0(drop, bool());

	MOCK_METHOD1(toJstring, jstring(const char*));
	MOCK_METHOD1(toString, string(jstring));
	MOCK_METHOD0(getJVM, JavaVM*());
	MOCK_METHOD3(getClassMethodId, jmethodID
		(const char*, const char*, const char*));
	MOCK_METHOD1(createGlobalRef, jobject(jobject));
	MOCK_METHOD1(deleteGlobalRef, void(jobject));
	MOCK_METHOD3(getObjectField, jobject(jobject, const char*, const char*));
	MOCK_METHOD3(getLongField, jlong(jobject obj, const char* fieldName,
		const char* sig));
	MOCK_METHOD4(setLongField, void(jobject obj, const char* fieldName,
		const char* sig, jlong value));
	MOCK_METHOD3(getMethodId, jmethodID(jobject, const char*, const char*));
	MOCK_METHOD5(callVoidMethod_LLO, void
		(jobject, jmethodID, jlong, jlong, jobject));
	MOCK_METHOD4(callVoidMethod_LO, void
		(jobject obj, jmethodID method, jlong, jobject));
	MOCK_METHOD6(createObject_LLDS, jobject(const char* className,
		const char* sig, jlong arg1, jlong arg2, jdouble arg3, jstring arg4));
	MOCK_METHOD3(createObject_L, jobject(const char* className,
		const char* sig, jlong arg1));
	MOCK_METHOD2(throwException, void(const char* className, const char* msg));
};
