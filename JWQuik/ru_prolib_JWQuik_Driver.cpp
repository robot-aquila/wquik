#include <wquik/WQuik.h>
#include <wquik/TransactionDriverException.h>
#include "jwquik/ru_prolib_JWQuik_Driver.h"
#include "jwquik/DriverCallbackTransfer.h"

namespace jwquik {

#define RETVOID /* VOID */
#define THROW_JAVA_EXCEPTION \
		helper->throwException("ru/prolib/JWQuik/DriverException", e.what());
#define START_METHOD(retval) \
	IJavaHelper* helper; \
	IDriverCallbackTransfer* transfer; \
	try { \
		helper = JavaWrapper::wrap(env); \
	} catch ( JavaHelperException e ) { \
		/* TODO: unable throw */ \
		printf("Cannot create java helper: %s\n", e.what()); \
		return retval; \
	}
#define END_METHOD \
	helper->drop();
#define GET_TRANSFER \
	(IDriverCallbackTransfer*)helper->getLongField(obj, "descriptor", "J")
#define IF_NOT_NULL(exp) \
	if ( transfer != 0 ) { \
		exp; \
	} else { \
		/* TODO: throw (object not initialized) */ \
		helper->throwException("ru/prolib/JWQuik/DriverException", "Object not initialized"); \
	}

JNIEXPORT void JNICALL Java_ru_prolib_JWQuik_Driver_init__
	(JNIEnv * env, jobject obj)
{
	ITransactionDriver* driver;
	START_METHOD(RETVOID);
	transfer = 0; // unused
	try {
		driver = WQuik::createDriver();
	} catch ( WQuikException e ) {
		THROW_JAVA_EXCEPTION;
		return;
	}
	Java_ru_prolib_JWQuik_Driver_init__J(env, obj, (jlong)driver);
	driver->drop();
	END_METHOD;
}

JNIEXPORT void JNICALL Java_ru_prolib_JWQuik_Driver_init__J
	(JNIEnv * env, jobject obj, jlong driver)
{
	START_METHOD(RETVOID);
	try {
		transfer = new DriverCallbackTransfer(helper,
			(ITransactionDriver*)driver, obj);
		helper->setLongField(obj, "descriptor", "J", (jlong)transfer);
	} catch ( JavaHelperException e ) {
		THROW_JAVA_EXCEPTION;
	}
	END_METHOD;
}

JNIEXPORT void JNICALL Java_ru_prolib_JWQuik_Driver_release
	(JNIEnv * env, jobject obj)
{
	START_METHOD(RETVOID);
	try {
		transfer = GET_TRANSFER;
		IF_NOT_NULL(
			helper->setLongField(obj, "descriptor", "J", 0);
			transfer->drop();
		);
	} catch ( JavaHelperException e ) {
		THROW_JAVA_EXCEPTION;
	}
	END_METHOD;
}

JNIEXPORT void JNICALL Java_ru_prolib_JWQuik_Driver_setAsyncMode
	(JNIEnv * env, jobject obj)
{
	START_METHOD(RETVOID);
	try {
		transfer = GET_TRANSFER;
		IF_NOT_NULL(
			transfer->getDriver()->setAsyncMode();
		);
	} catch ( JavaHelperException e ) {
		THROW_JAVA_EXCEPTION;
	} catch ( TransactionDriverException e ) {
		THROW_JAVA_EXCEPTION;
	}
	END_METHOD;
}

JNIEXPORT void JNICALL Java_ru_prolib_JWQuik_Driver_setSyncMode
	(JNIEnv * env, jobject obj)
{
	START_METHOD(RETVOID);
	try {
		transfer = GET_TRANSFER;
		IF_NOT_NULL(
			transfer->getDriver()->setSyncMode();
		);
	} catch ( JavaHelperException e ) {
		THROW_JAVA_EXCEPTION;
	} catch ( TransactionDriverException e ) {
		THROW_JAVA_EXCEPTION;
	}
	END_METHOD;
}

JNIEXPORT jboolean JNICALL Java_ru_prolib_JWQuik_Driver_isSyncMode
	(JNIEnv * env, jobject obj)
{
	jboolean result = JNI_FALSE;
	START_METHOD(result);
	try {
		transfer = GET_TRANSFER;
		IF_NOT_NULL(
			result = (transfer->getDriver()
				->isSyncMode() ? JNI_TRUE : JNI_FALSE);
		);
	} catch ( JavaHelperException e ) {
		THROW_JAVA_EXCEPTION;
	}
	END_METHOD;
	return result;
}

JNIEXPORT jboolean JNICALL Java_ru_prolib_JWQuik_Driver_isAsyncMode
	(JNIEnv * env, jobject obj)
{
	jboolean result = JNI_FALSE;
	START_METHOD(result);
	try {
		transfer = GET_TRANSFER;
		IF_NOT_NULL(
			result = (transfer->getDriver()
				->isAsyncMode() ? JNI_TRUE : JNI_FALSE);
		);
	} catch ( JavaHelperException e ) {
		THROW_JAVA_EXCEPTION;
	}
	END_METHOD;
	return result;
}

JNIEXPORT void JNICALL Java_ru_prolib_JWQuik_Driver_connect
	(JNIEnv * env, jobject obj, jstring jstr)
{
	START_METHOD(RETVOID);
	try {
		transfer = GET_TRANSFER;
		IF_NOT_NULL(
			transfer->getDriver()->connect(helper->toString(jstr).c_str());
		);
	} catch ( JavaHelperException e ) {
		THROW_JAVA_EXCEPTION;
	} catch ( TransactionDriverException e ) {
		THROW_JAVA_EXCEPTION;
	}
	END_METHOD;
}

JNIEXPORT void JNICALL Java_ru_prolib_JWQuik_Driver_disconnect
	(JNIEnv * env, jobject obj)
{
	START_METHOD(RETVOID);
	try {
		transfer = GET_TRANSFER;
		IF_NOT_NULL(
			transfer->getDriver()->disconnect();
		);
	} catch ( TransactionDriverException e ) {
		THROW_JAVA_EXCEPTION;
	}
	END_METHOD;
}

JNIEXPORT jboolean JNICALL Java_ru_prolib_JWQuik_Driver_isQuikConnected
	(JNIEnv * env, jobject obj)
{
	jboolean result = JNI_FALSE;
	START_METHOD(result);
	try {
		transfer = GET_TRANSFER;
		IF_NOT_NULL(
			result = (transfer->getDriver()
				->isQuikConnected() ? JNI_TRUE : JNI_FALSE);
		);
	} catch ( JavaHelperException e ) {
		THROW_JAVA_EXCEPTION;
	} catch ( TransactionDriverException e ) {
		THROW_JAVA_EXCEPTION;
	}
	END_METHOD;
	return result;
}

JNIEXPORT jboolean JNICALL Java_ru_prolib_JWQuik_Driver_isDllConnected
	(JNIEnv * env, jobject obj)
{
	jboolean result = JNI_FALSE;
	START_METHOD(result);
	try {
		transfer = GET_TRANSFER;
		IF_NOT_NULL(
			result = (transfer->getDriver()
				->isDllConnected() ? JNI_TRUE : JNI_FALSE);
		);
	} catch ( JavaHelperException e ) {
		THROW_JAVA_EXCEPTION;
	} catch ( TransactionDriverException e ) {
		THROW_JAVA_EXCEPTION;
	}
	END_METHOD;
	return result;
}

JNIEXPORT jobject JNICALL Java_ru_prolib_JWQuik_Driver_sendSyncTransaction
	(JNIEnv * env, jobject obj, jstring transString)
{
	TransactionResult tr;
	jobject result = NULL;
	START_METHOD(result);
	try {
		transfer = GET_TRANSFER;
		IF_NOT_NULL(
			transfer->getDriver()->sendSyncTransaction
				(helper->toString(transString).c_str(), &tr);
			result = helper->createObject_LLDS
				("ru/prolib/JWQuik/Driver$TransactionResult",
				"(JJDLjava/lang/String;)V", tr.replyCode, tr.transId,
				tr.orderNumber, helper->toJstring(tr.resultMessage.c_str()));
		);
	} catch ( JavaHelperException e ) {
		THROW_JAVA_EXCEPTION;
	} catch ( TransactionDriverException e ) {
		THROW_JAVA_EXCEPTION;
	}
	END_METHOD;
	return result;
}

JNIEXPORT void JNICALL Java_ru_prolib_JWQuik_Driver_sendAsyncTransaction
	(JNIEnv * env, jobject obj, jstring transString)
{
	START_METHOD(RETVOID);
	try {
		transfer = GET_TRANSFER;
		IF_NOT_NULL(
			transfer->getDriver()->sendAsyncTransaction
				(helper->toString(transString).c_str());
		);
	} catch ( JavaHelperException e ) {
		THROW_JAVA_EXCEPTION;
	} catch ( TransactionDriverException e ) {
		THROW_JAVA_EXCEPTION;
	}
	END_METHOD;
}

} // end namespace jwquik

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *jvm, void *reserved) {
	try {
		jwquik::JavaWrapper::init(jvm);
	} catch ( jwquik::JavaHelperException e ) {
		printf("JWQUIK[E]: %s\n", e.what());
		return JNI_ERR;
	}
     return JNI_VERSION_1_2;
}

JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *jvm, void *reserved) {
	try {
		jwquik::JavaWrapper::free(jvm);
	} catch ( jwquik::JavaHelperException e ) {
		printf("JWQUIK[E]: %s\n", e.what());
	}
}

