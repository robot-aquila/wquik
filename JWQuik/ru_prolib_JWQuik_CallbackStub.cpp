#include "jwquik/JWQuik.h"
#include "jwquik/ru_prolib_JWQuik_CallbackStub.h"

namespace jwquik {

#define JWQUIK_CBSTUB_INIT \
	jclass cls; \
	jfieldID fld; \
	ICallbackStub* cb; \
	cls = env->FindClass(JWQUIK_CBSTUB_CLASS); \
	if ( cls == NULL ) { \
		JWQUIK_THROW(env, JWQUIK_EXCEPTION_CLASS, "CallbackStub class not found", JWQUIK_VOID) \
		return; \
	} \
	fld = env->GetFieldID(cls, JWQUIK_CBSTUB_DESCRIPTOR_FIELD, JWQUIK_CBSTUB_DESCRIPTOR_SIG); \
	if ( fld == NULL ) { \
		JWQUIK_THROW(env, JWQUIK_EXCEPTION_CLASS, "CallbackStub descriptor field not found", JWQUIK_VOID) \
		return; \
	} \
	cb = (ICallbackStub*)env->GetLongField(obj, fld); \
	if ( cb == 0 ) { \
		JWQUIK_THROW(env, JWQUIK_EXCEPTION_CLASS, "CallbackStub not initialized", JWQUIK_VOID) \
		return; \
	}

JNIEXPORT void JNICALL Java_ru_prolib_JWQuik_CallbackStub_init
	(JNIEnv * env, jobject obj)
{

}

JNIEXPORT void JNICALL Java_ru_prolib_JWQuik_CallbackStub_release
	(JNIEnv * env, jobject obj)
{
	JWQUIK_CBSTUB_INIT;
	env->SetLongField(obj, fld, 0);
}

JNIEXPORT void JNICALL Java_ru_prolib_JWQuik_CallbackStub_onConnectionStatus
	(JNIEnv * env, jobject obj, jlong eventId , jlong errCode, jstring message)
{
	JWQUIK_CBSTUB_INIT;
	cb->onConnectionStatus(env, obj, eventId, errCode, message);
}

JNIEXPORT void JNICALL Java_ru_prolib_JWQuik_CallbackStub_onOrderStatus
	(JNIEnv * env, jobject obj, jlong mode, jobject order)
{
	JWQUIK_CBSTUB_INIT;
	cb->onOrderStatus(env, obj, mode, order);
}

JNIEXPORT void JNICALL Java_ru_prolib_JWQuik_CallbackStub_onTradeStatus
	(JNIEnv * env, jobject obj, jlong mode, jobject trade)
{
	JWQUIK_CBSTUB_INIT;
	cb->onTradeStatus(env, obj, mode, trade);
}

JNIEXPORT void JNICALL Java_ru_prolib_JWQuik_CallbackStub_onTransactionReply
	(JNIEnv * env, jobject obj, jlong result, jlong errCode, jobject tr)
{
	JWQUIK_CBSTUB_INIT;
	cb->onTransactionReply(env, obj, result, errCode, tr);
}

} // end namespace jwquik
