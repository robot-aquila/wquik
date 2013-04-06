#pragma once
#include <jwquik/JavaWrapper.h>
#include <jwquik/JWQuik.h>

namespace jwquik {

class JavaHelper : public IJavaHelper {
public:
	JavaHelper(JNIEnv* env, jclass order_class, jclass trade_class,
		jclass result_class);
	JavaHelper(JavaVM* jvm, jclass order_class, jclass trade_class,
		jclass result_class);
	virtual ~JavaHelper(void);
	virtual jstring toJstring(const char* str);
	virtual string toString(jstring jstr);
	virtual JavaVM* getJVM();
	virtual jmethodID getClassMethodId
		(const char* className, const char* methodName, const char* sig);
	virtual jobject createGlobalRef(jobject);
	virtual void deleteGlobalRef(jobject);
	virtual jobject getObjectField
		(jobject obj, const char* fieldName, const char* sig);
	virtual jlong getLongField(jobject obj, const char* fieldName,
		const char* sig);
	virtual void setLongField(jobject obj, const char* fieldName,
		const char* sig, jlong value);
	virtual jmethodID getMethodId
		(jobject obj, const char* methodName, const char* sig);
	virtual void callVoidMethod_LLO
		(jobject obj, jmethodID method, jlong, jlong, jobject);
	virtual void callVoidMethod_LO
		(jobject obj, jmethodID method, jlong arg1, jobject arg2);
	virtual jobject createObject_LLDS(const char* className, const char* sig,
		jlong arg1, jlong arg2, jdouble arg3, jstring arg4);
	virtual jobject createObject_L(const char* className, const char* sig,
		jlong arg1);
	virtual void throwException(const char* className, const char* msg);

private:
	jclass findClass(const char* className);

private:
	JNIEnv* env;
	JavaVM* jvm;
	jclass orderClass;
	jclass tradeClass;
	jclass resultClass;
};

} // end namespace jwquik
