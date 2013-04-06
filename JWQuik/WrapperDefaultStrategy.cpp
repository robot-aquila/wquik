#include <jwquik/WrapperDefaultStrategy.h>
#include <jwquik/JavaHelper.h>
#include <jwquik/JWQuik.h>

namespace jwquik {

WrapperDefaultStrategy::WrapperDefaultStrategy(void) {
	orderClass = tradeClass = transResultClass = 0;
}

WrapperDefaultStrategy::~WrapperDefaultStrategy(void) {
}

IJavaHelper* WrapperDefaultStrategy::produce(JNIEnv* env) {
	if ( orderClass == 0 || tradeClass == 0 || transResultClass == 0 ) {
		throw JavaHelperException("Wrapper not initialized");
	}
	return new JavaHelper(env, (jclass)orderClass,
		(jclass)tradeClass, (jclass)transResultClass);
}

IJavaHelper* WrapperDefaultStrategy::produce(JavaVM* jvm) {
	if ( orderClass == 0 || tradeClass == 0 || transResultClass == 0 ) {
		throw JavaHelperException("Wrapper not initialized");
	}
	return new JavaHelper(jvm, (jclass)orderClass,
		(jclass)tradeClass, (jclass)transResultClass);
}

void WrapperDefaultStrategy::init(JavaVM* jvm) {
	JNIEnv *env;
	if ( jvm->GetEnv((void **)&env, JNI_VERSION_1_2) < 0 ) {
		throw JavaHelperException("Could not obtain java environment");
	}
	orderClass = env->FindClass(JWQUIK_ORDER_CLASS);
	if ( orderClass == 0 ) {
		throw JavaHelperException
			((string)"Class not found: " + JWQUIK_ORDER_CLASS);
	}
	tradeClass = env->FindClass(JWQUIK_TRADE_CLASS);
	if ( tradeClass == 0 ) {
		throw JavaHelperException
			((string)"Class not found: " + JWQUIK_TRADE_CLASS);
	}
	transResultClass = env->FindClass(JWQUIK_TRANSRESULT_CLASS);
	if ( transResultClass == 0 ) {
		throw JavaHelperException
			((string)"Class not found: " + JWQUIK_TRANSRESULT_CLASS);
	}
	orderClass = env->NewWeakGlobalRef(orderClass);
	tradeClass = env->NewWeakGlobalRef(tradeClass);
	transResultClass = env->NewWeakGlobalRef(transResultClass);
}

void WrapperDefaultStrategy::free(JavaVM* jvm) {
	JNIEnv *env;
	if ( jvm->GetEnv((void **)&env, JNI_VERSION_1_2) < 0 ) {
		throw JavaHelperException("Could not obtain java environment");
	}
	if ( orderClass == 0 || tradeClass == 0 || transResultClass == 0 ) {
		throw JavaHelperException("Wrapper not initialized");
	}
	env->DeleteWeakGlobalRef(orderClass);
	env->DeleteWeakGlobalRef(tradeClass);
	env->DeleteWeakGlobalRef(transResultClass);
	orderClass = tradeClass = transResultClass = 0;
}

} // end namespace jwquik
