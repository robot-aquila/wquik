#pragma once
#include <jni.h>
#include <string>

using namespace std;

namespace jwquik {

class ICallbackStub {
public:
	virtual ~ICallbackStub(void){};
	virtual void onConnectionStatus(JNIEnv *, jobject, jlong, jlong, jstring)=0;
	virtual void onOrderStatus(JNIEnv *, jobject, jlong, jobject)=0;
	virtual void onTradeStatus(JNIEnv *, jobject, jlong, jobject)=0;
	virtual void onTransactionReply(JNIEnv *, jobject, jlong, jlong, jobject)=0;
};

#define JWQUIK_CBSTUB_CLASS				"ru/prolib/JWQuik/CallbackStub"
#define JWQUIK_CBSTUB_DESCRIPTOR_FIELD	"descriptor"
#define JWQUIK_CBSTUB_DESCRIPTOR_SIG	"J"
#define JWQUIK_ORDER_CLASS				"ru/prolib/JWQuik/Driver$Order"
#define JWQUIK_ORDER_DESCRIPTOR_FIELD	"descriptor"
#define JWQUIK_ORDER_DESCRIPTOR_SIG		"J"
#define JWQUIK_TRADE_CLASS				"ru/prolib/JWQuik/Driver$Trade"
#define JWQUIK_TRADE_DESCRIPTOR_FIELD	"descriptor"
#define JWQUIK_TRADE_DESCRIPTOR_SIG		"J"
#define JWQUIK_DRIVER_CLASS				"ru/prolib/JWQuik/Driver"
#define JWQUIK_DRIVER_DESCRIPTOR_FIELD	"descriptor"
#define JWQUIK_DRIVER_DESCRIPTOR_SIG	"J"
#define JWQUIK_TRANSRESULT_CLASS		"ru/prolib/JWQuik/Driver$TransactionResult"

#define JWQUIK_EXCEPTION_CLASS "ru/prolib/JWQuik/DriverException"
#define JWQUIK_VOID /* void */

#define JWQUIK_THROW(env, exClass, msg, retval) \
	{ \
		jclass exc; \
		exc = env->FindClass(exClass); \
		if ( exc == 0 ) { \
			printf("Internal error: class %s not found\n", exClass); \
			return retval; \
		} \
		env->ThrowNew(exc, msg); \
		return retval; \
	}

#define JWQUIK_RETJSTRING(str) \
	if ( str == NULL ) { \
		return env->NewString((const jchar*)"", 0); \
	} \
	string s = str; \
	wstring ws(L""); \
	char ch; \
	wchar_t wch; \
	for ( size_t i = 0; i < s.length(); i ++ ) { \
		ch = s.at(i); \
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, &ch, 1, &wch, 1); \
		ws += wch; \
	} \
	return env->NewString((jchar*)ws.c_str(), (jsize)ws.length());


#define JWQUIK_ORDER_INIT(retval) \
	jclass cls; \
	jfieldID fld; \
	IOrder* order; \
	cls = env->FindClass(JWQUIK_ORDER_CLASS); \
	if ( cls == NULL ) { \
		JWQUIK_THROW(env, JWQUIK_EXCEPTION_CLASS, "Order class not found", retval) \
		return retval; \
	} \
	fld = env->GetFieldID(cls, JWQUIK_ORDER_DESCRIPTOR_FIELD, JWQUIK_ORDER_DESCRIPTOR_SIG); \
	if ( fld == NULL ) { \
		JWQUIK_THROW(env, JWQUIK_EXCEPTION_CLASS, "Order descriptor field not found", retval) \
		return retval; \
	} \
	order = (IOrder*)env->GetLongField(obj, fld);

#define JWQUIK_TRADE_INIT(retval) \
	jclass cls; \
	jfieldID fld; \
	ITrade* trade; \
	cls = env->FindClass(JWQUIK_TRADE_CLASS); \
	if ( cls == NULL ) { \
		JWQUIK_THROW(env, JWQUIK_EXCEPTION_CLASS, "Trade class not found", retval) \
		return retval; \
	} \
	fld = env->GetFieldID(cls, JWQUIK_TRADE_DESCRIPTOR_FIELD, JWQUIK_TRADE_DESCRIPTOR_SIG); \
	if ( fld == NULL ) { \
		JWQUIK_THROW(env, JWQUIK_EXCEPTION_CLASS, "Trade descriptor field not found", retval) \
		return retval; \
	} \
	trade = (ITrade*)env->GetLongField(obj, fld);

#define JWQUIK_DRIVER_INIT(retval) \
	jclass cls; \
	jfieldID fld; \
	DriverCallbackTransfer* transfer; \
	cls = env->FindClass(JWQUIK_DRIVER_CLASS); \
	if ( cls == NULL ) { \
		JWQUIK_THROW(env, JWQUIK_EXCEPTION_CLASS, "Driver class not found", retval) \
		return retval; \
	} \
	fld = env->GetFieldID(cls, JWQUIK_DRIVER_DESCRIPTOR_FIELD, JWQUIK_DRIVER_DESCRIPTOR_SIG); \
	if ( fld == NULL ) { \
		JWQUIK_THROW(env, JWQUIK_EXCEPTION_CLASS, "Driver descriptor field not found", retval) \
		return retval; \
	} \
	transfer = (DriverCallbackTransfer*)env->GetLongField(obj, fld);


#define JWQUIK_ORDER_TEST(retval) \
	if ( order == 0 ) { \
		JWQUIK_THROW(env, JWQUIK_EXCEPTION_CLASS, "Order not initialized", retval) \
		return retval; \
	}

#define JWQUIK_DRIVER_TEST(retval) \
	if ( transfer == 0 ) { \
		JWQUIK_THROW(env, JWQUIK_EXCEPTION_CLASS, "Driver not initialized", retval) \
		return retval; \
	}

#define JWQUIK_TRADE_TEST(retval) \
	if ( trade == 0 ) { \
		JWQUIK_THROW(env, JWQUIK_EXCEPTION_CLASS, "Trade not initialized", retval) \
		return retval; \
	}

#define JWQUIK_ORDER_INITTEST(retval) \
	JWQUIK_ORDER_INIT(retval); \
	JWQUIK_ORDER_TEST(retval);

#define JWQUIK_DRIVER_INITTEST(retval) \
	JWQUIK_DRIVER_INIT(retval); \
	JWQUIK_DRIVER_TEST(retval);

#define JWQUIK_TRADE_INITTEST(retval) \
	JWQUIK_TRADE_INIT(retval); \
	JWQUIK_TRADE_TEST(retval);

#define JWQUIK_ORDER_FN(fn) Java_ru_prolib_JWQuik_Driver_00024Order_ ## fn

#define JWQUIK_TRADE_FN(fn) Java_ru_prolib_JWQuik_Driver_00024Trade_ ## fn

#define JWQUIK_ORDER_CALL(fn) order-> ## fn

#define JWQUIK_TRADE_CALL(fn) trade-> ## fn

#define JWQUIK_ORDER_FNPROTO(fn, rettype) \
	JNIEXPORT rettype JNICALL JWQUIK_ORDER_FN(fn)(JNIEnv * env, jobject obj)

#define JWQUIK_TRADE_FNPROTO(fn, rettype) \
	JNIEXPORT rettype JNICALL JWQUIK_TRADE_FN(fn)(JNIEnv * env, jobject obj)

#define JWQUIK_ORDER_GETTER(fn, rettype, retval) \
	JWQUIK_ORDER_FNPROTO(fn, rettype) { \
	JWQUIK_ORDER_INITTEST(retval); \
	return JWQUIK_ORDER_CALL(fn)(); \
}

#define JWQUIK_TRADE_GETTER(fn, rettype, retval) \
	JWQUIK_TRADE_FNPROTO(fn, rettype) { \
	JWQUIK_TRADE_INITTEST(retval); \
	return JWQUIK_TRADE_CALL(fn)(); \
}

#define JWQUIK_ORDER_GETTER_STR(fn) \
	JWQUIK_ORDER_FNPROTO(fn, jstring) { \
	JWQUIK_ORDER_INITTEST(0); \
	const char* str = JWQUIK_ORDER_CALL(fn)(); \
	JWQUIK_RETJSTRING(str); \
}

#define JWQUIK_TRADE_GETTER_STR(fn) \
	JWQUIK_TRADE_FNPROTO(fn, jstring) { \
	JWQUIK_TRADE_INITTEST(0); \
	const char* str = JWQUIK_TRADE_CALL(fn)(); \
	JWQUIK_RETJSTRING(str); \
}

} // end namespace jwquik
