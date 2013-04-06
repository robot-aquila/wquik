#include <jwquik/JavaHelper.h>
#include <windows.h>

namespace jwquik {

JavaHelper::JavaHelper(JNIEnv* env, jclass order_class,
					   jclass trade_class, jclass result_class)
: orderClass(order_class), tradeClass(trade_class), resultClass(result_class)
{
	this->jvm = 0;
	this->env = env;
}

JavaHelper::JavaHelper(JavaVM* jvm, jclass order_class,
					   jclass trade_class, jclass result_class)
: orderClass(order_class), tradeClass(trade_class), resultClass(result_class)
{
	this->jvm = jvm;
	if ( jvm->AttachCurrentThread((void**)&env, 0) < 0 ) {
		throw JavaHelperException("Attach current thread failed");
	}
	/*
	try {
		setupThread();
	} catch ( ... ) {
		jvm->DetachCurrentThread();
		throw;
	}
	*/
}

JavaHelper::~JavaHelper(void) {
	if ( jvm != 0 ) {
		jvm->DetachCurrentThread();
	}
}

jstring JavaHelper::toJstring(const char* str) {
	if ( str == NULL ) {
		return env->NewString((const jchar*)"", 0);
	}
	string s = str;
	wstring ws(L"");
	char ch;
	wchar_t wch;
	for ( size_t i = 0; i < s.length(); i ++ ) {
		ch = s.at(i);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, &ch, 1, &wch, 1);
		ws += wch;
	}
	return env->NewString((jchar*)ws.c_str(), (jsize)ws.length());
}

string JavaHelper::toString(jstring jstr) {
	const WCHAR *cstr = (const WCHAR*)env->GetStringChars(jstr, JNI_FALSE);
	wstring wstr(cstr);
	string str;
	
	jsize length = env->GetStringLength(jstr);
	char ch;
	wchar_t wch;
	for ( jsize i = 0; i < length; i ++ ) {
		wch = wstr.at(i);
		WideCharToMultiByte(CP_ACP, 0, &wch, 1, &ch, 1, NULL, NULL);
		str += ch;
	}
	env->ReleaseStringChars(jstr, (const jchar*)cstr);
	return str;
}

JavaVM* JavaHelper::getJVM() {
	if ( jvm != 0 ) {
		return jvm;
	}
	JavaVM* javaVm;
	if ( env->GetJavaVM(&javaVm) < 0 ) {
		throw JavaHelperException("Could not obtain java VM");
	}
	return javaVm;
}

jclass JavaHelper::findClass(const char* className) {
	jclass classId = 0;
	if ( strcmp(className, JWQUIK_TRANSRESULT_CLASS) == 0 ) {
		classId = resultClass;
	} else if ( strcmp(className, JWQUIK_ORDER_CLASS) == 0 ) {
		classId = orderClass;
	} else if ( strcmp(className, JWQUIK_TRADE_CLASS) == 0 ) {
		classId = tradeClass;
	} else {
		classId = env->FindClass(className);
	}
	if ( classId == 0 ) {
		throw JavaHelperException((string)"Class not found: " + className);
	}
	return classId;
}

jmethodID JavaHelper::getClassMethodId
	(const char* className, const char* methodName, const char* sig)
{
	jmethodID methodId = env->GetMethodID(findClass(className),
		methodName, sig);
	if ( methodId == 0 ) {
		throw JavaHelperException((string)"Method not found: " + className
			+ "::" + methodName + "[" + sig + "]");
	}
	return methodId;
}

jobject JavaHelper::createGlobalRef(jobject obj) {
	jobject ref = env->NewGlobalRef(obj);
	if ( ref == 0 ) {
		throw JavaHelperException("Could not create global reference");
	}
	return ref;
}

void JavaHelper::deleteGlobalRef(jobject obj) {
	env->DeleteGlobalRef(obj);
}

jobject JavaHelper::getObjectField
	(jobject obj, const char* fieldName, const char* sig)
{
	jclass classId = env->GetObjectClass(obj);
	if ( classId == 0 ) {
		throw JavaHelperException("Could not obtain object class");
	}
	jfieldID fieldId = env->GetFieldID(classId, fieldName, sig);
	if ( fieldId == 0 ) {
		throw JavaHelperException((string)"Could not obtain field ID: "
			+ fieldName + "[" + sig + "]");
	}
	return env->GetObjectField(obj, fieldId);
}

jmethodID JavaHelper::getMethodId
	(jobject obj, const char* methodName, const char* sig)
{
	jclass classId = env->GetObjectClass(obj);
	if ( classId == 0 ) {
		throw JavaHelperException("Could not obtain object class");
	}
	jmethodID methodId = env->GetMethodID(classId, methodName, sig);
	if ( methodId == 0 ) {
		throw JavaHelperException((string)"Could not obtain method ID: "
			+ methodName + "[" + sig + "]");
	}
	return methodId;
}

void JavaHelper::callVoidMethod_LLO
	(jobject obj, jmethodID method, jlong arg1, jlong arg2, jobject arg3)
{
	env->CallVoidMethod(obj, method, arg1, arg2, arg3);
}

void JavaHelper::callVoidMethod_LO
	(jobject obj, jmethodID method, jlong arg1, jobject arg2)
{
	env->CallVoidMethod(obj, method, arg1, arg2);
}

jobject JavaHelper::createObject_LLDS(const char* className, const char* sig,
	jlong arg1, jlong arg2, jdouble arg3, jstring arg4)
{
	jclass classId = findClass(className);
	jmethodID methodId = env->GetMethodID(classId, "<init>", sig);
	if ( methodId == 0 ) {
		throw JavaHelperException((string)"Constructor not found: " + sig);
	}
	return env->NewObject(classId, methodId, arg1, arg2, arg3, arg4);
}

jobject JavaHelper::createObject_L(const char* className, const char* sig,
	jlong arg1)
{
	jclass classId = findClass(className);
	jmethodID methodId = env->GetMethodID(classId, "<init>", sig);
	if ( methodId == 0 ) {
		throw JavaHelperException((string)"Constructor not found: " + sig);
	}
	return env->NewObject(classId, methodId, arg1);
}

jlong JavaHelper::getLongField(jobject obj, const char* fieldName,
							   const char* sig)
{
	jclass classId = env->GetObjectClass(obj);
	if ( classId == 0 ) {
		throw JavaHelperException("Could not obtain object class");
	}
	jfieldID fieldId = env->GetFieldID(classId, fieldName, sig);
	if ( fieldId == 0 ) {
		throw JavaHelperException((string)"Could not obtain field ID: "
			+ fieldName + "[" + sig + "]");
	}
	return env->GetLongField(obj, fieldId);
}

void JavaHelper::setLongField(jobject obj, const char* fieldName,
							  const char* sig, jlong value)
{
	jclass classId = env->GetObjectClass(obj);
	if ( classId == 0 ) {
		throw JavaHelperException("Could not obtain object class");
	}
	jfieldID fieldId = env->GetFieldID(classId, fieldName, sig);
	if ( fieldId == 0 ) {
		throw JavaHelperException((string)"Could not obtain field ID: "
			+ fieldName + "[" + sig + "]");
	}
	env->SetLongField(obj, fieldId, value);
}

void JavaHelper::throwException(const char* className, const char* msg) {
	env->ThrowNew(findClass(className), msg);
}

} // end namespace jwquik
