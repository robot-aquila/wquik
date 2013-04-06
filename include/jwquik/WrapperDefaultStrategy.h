#pragma once
#include <jwquik/JavaWrapper.h>

namespace jwquik {

class WrapperDefaultStrategy : public IWrapperStrategy {
public:
	WrapperDefaultStrategy(void);
	virtual ~WrapperDefaultStrategy(void);
	virtual IJavaHelper* produce(JNIEnv* env);
	virtual IJavaHelper* produce(JavaVM* jvm);
	virtual void init(JavaVM* jvm);
	virtual void free(JavaVM* jvm);
private:
	jweak orderClass;
	jweak tradeClass;
	jweak transResultClass;
};

} // end namespace jwquik
