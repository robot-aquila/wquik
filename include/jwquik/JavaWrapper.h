#pragma once
#include <jni.h>
#include <string>
#include <exception>
#include <aquila/core/IReferenceCounted.h>

using namespace std;
using namespace aquila::core;

namespace jwquik {

#ifdef JWQUIK_EXPORTS
#define JWQUIKAPI __declspec(dllexport)
#else
#define JWQUIKAPI __declspec(dllimport)
#endif

class JavaHelperException : public std::exception {
public:
	virtual ~JavaHelperException(void){};
	JavaHelperException(string & str) { msg = str; }
	JavaHelperException(const char* text) { msg = text; }
	virtual const char* what() const throw() { return msg.c_str(); }
private:
	string msg;
};

class IJavaHelper : public IReferenceCounted {
public:
	virtual ~IJavaHelper(void){};
	virtual jstring toJstring(const char* str)=0;
	virtual string toString(jstring jstr)=0;
	virtual JavaVM* getJVM()=0;
	virtual jmethodID getClassMethodId(const char* className,
		const char* methodName, const char* sig)=0;
	virtual jobject createGlobalRef(jobject)=0;
	virtual void deleteGlobalRef(jobject)=0;

	virtual jobject getObjectField(jobject obj, const char* fieldName,
		const char* sig)=0;
	virtual jlong getLongField(jobject obj, const char* fieldName,
		const char* sig)=0;
	virtual void setLongField(jobject obj, const char* fieldName,
		const char* sig, jlong value)=0;

	virtual jmethodID getMethodId(jobject obj, const char* methodName,
		const char* sig)=0;
	virtual void callVoidMethod_LLO(jobject obj, jmethodID method, jlong,
		jlong, jobject)=0;
	virtual void callVoidMethod_LO(jobject obj, jmethodID method, jlong,
		jobject)=0;
	virtual jobject createObject_LLDS(const char* className, const char* sig,
		jlong arg1, jlong arg2, jdouble arg3, jstring arg4)=0;
	virtual jobject createObject_L(const char* className, const char* sig,
		jlong arg1)=0;
	virtual void throwException(const char* className, const char* msg)=0;
};

/**
 * Стратегия оборачивания элементов Java определяет интерфейс, через который
 * синглтон-фасад JavaWrapper получает доступ к конструкторам оберток.
 */
class IWrapperStrategy : public IReferenceCounted {
public:
	virtual ~IWrapperStrategy(void){};
	virtual void init(JavaVM* jvm)=0;
	virtual void free(JavaVM* jvm)=0;
	virtual IJavaHelper* produce(JNIEnv* env)=0;
	virtual IJavaHelper* produce(JavaVM* jvm)=0;
};

/**
 * Фасад к функциям оборачивания элементов java. Так как доступ к этим
 * функциям может потребоваться из любого места программы, реализован в
 * виде набора статических методов. Позволяет менять стратегию обслуживания
 * путем установки единственного глобального экземпляра стратегии
 * оборачивания.
 */
class JavaWrapper {
public:
	static JWQUIKAPI IJavaHelper* wrap(JNIEnv* env);
	static JWQUIKAPI IJavaHelper* wrap(JavaVM* jvm);
	static JWQUIKAPI void setStrategy(IWrapperStrategy* wrapperStrategy);
	static JWQUIKAPI IWrapperStrategy* getStrategy();
	static JWQUIKAPI void init(JavaVM* jvm);
	static JWQUIKAPI void free(JavaVM* jvm);
private:
	static IWrapperStrategy* strategy;
};

} // end namespace jwquik
