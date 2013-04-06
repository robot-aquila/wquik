#pragma once

#define ASSERT_JBOOL(expected, actual) \
	ASSERT_EQ((expected ? JNI_TRUE : JNI_FALSE), actual);

#define ASSERT_JSTREQ(expected, actual) \
	const WCHAR *cstr = (const WCHAR*)env->GetStringChars(actual, JNI_FALSE); \
	wstring a(cstr); \
	env->ReleaseStringChars(actual, (const jchar*)cstr); \
	wstring e(L ## expected); \
	ASSERT_EQ(e, a);

#define JWQUIK_TEST_GETTER(testClass, mock, method, sig, retval, rettype, jmethod, assertMacro) \
	TEST_F(testClass, test_ ## method) { \
		EXPECT_CONSTRUCTOR_CALLS(); \
		EXPECT_CALL(mock, method ## ()) \
			.Times(1) \
			.WillOnce(Return(retval)); \
		jobject obj = env->NewObject(classId, constructorId, (jlong)& ## mock); \
		ASSERT_EQ(NULL, env->ExceptionOccurred()); \
		ASSERT_NE((jobject)NULL, obj); \
		jmethodID m = env->GetMethodID(classId, #method, sig); \
		rettype val = (rettype)env-> ## jmethod ## (obj, m); \
		assertMacro ## (retval, val); \
}

#define JWQUIK_TEST_GETTER_D(testClass, mock, method, retval) \
	JWQUIK_TEST_GETTER(testClass, mock, method, "()D", retval, jdouble, CallDoubleMethod, ASSERT_EQ)

#define JWQUIK_TEST_GETTER_L(testClass, mock, method, retval) \
	JWQUIK_TEST_GETTER(testClass, mock, method, "()J", retval, jlong, CallLongMethod, ASSERT_EQ)

#define JWQUIK_TEST_GETTER_B(testClass, mock, method, retval) \
	JWQUIK_TEST_GETTER(testClass, mock, method, "()Z", retval, jboolean, CallBooleanMethod, ASSERT_JBOOL)

#define JWQUIK_TEST_GETTER_S(testClass, mock, method, retval) \
	JWQUIK_TEST_GETTER(testClass, mock, method, "()Ljava/lang/String;", retval, jstring, CallObjectMethod, ASSERT_JSTREQ)