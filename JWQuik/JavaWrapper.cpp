#include <jwquik/JavaWrapper.h>
#include <jwquik/WrapperDefaultStrategy.h>

namespace jwquik {

IWrapperStrategy* JavaWrapper::strategy = 0;

JWQUIKAPI IJavaHelper* JavaWrapper::wrap(JNIEnv* env) {
	return getStrategy()->produce(env);
}

JWQUIKAPI IJavaHelper* JavaWrapper::wrap(JavaVM* jvm) {
	return getStrategy()->produce(jvm);
}

JWQUIKAPI void JavaWrapper::setStrategy(IWrapperStrategy* wrapperStrategy) {
	if ( strategy != 0 && strategy != wrapperStrategy ) {
		strategy->drop();
	}
	if ( wrapperStrategy != 0 ) {
		strategy = (IWrapperStrategy*)wrapperStrategy->grab();
	} else {
		strategy = 0;
	}
}

JWQUIKAPI IWrapperStrategy* JavaWrapper::getStrategy() {
	if ( strategy == 0 ) {
		strategy = new WrapperDefaultStrategy();
	}
	return strategy;
}

JWQUIKAPI void JavaWrapper::init(JavaVM* jvm) {
	getStrategy()->init(jvm);
}

JWQUIKAPI void JavaWrapper::free(JavaVM* jvm) {
	getStrategy()->free(jvm);
}
	
} // end namespace jwquik
