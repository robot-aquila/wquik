#include "jwquik/DriverCallbackTransfer.h"

namespace jwquik {

#define JWQUIK_GET_CALLBACK(helper) helper->getObjectField(instance, \
	"callback", "Lru/prolib/JWQuik/ICallback;")

JWQUIKAPI DriverCallbackTransfer::DriverCallbackTransfer
	(IJavaHelper* helper, ITransactionDriver* drv, jobject obj)
{
	instance = 0;
	driver = 0;
	jvm = helper->getJVM();
	instance = helper->createGlobalRef(obj);
	driver = (ITransactionDriver*)drv->grab();
	driver->setCallbackHandler(this);
}

JWQUIKAPI DriverCallbackTransfer::~DriverCallbackTransfer(void) {
	driver->drop();
	IJavaHelper* helper = JavaWrapper::wrap(jvm);
	helper->deleteGlobalRef(instance);
	helper->drop();
}

JWQUIKAPI ITransactionDriver* DriverCallbackTransfer::getDriver() {
	return driver;
}

void DriverCallbackTransfer::onConnectionStatus
	(long eventId, long errorCode, const char* message)
{
	IJavaHelper* helper;
	jobject callback;
	jmethodID method;
	try {
		helper = JavaWrapper::wrap(jvm);
	} catch ( JavaHelperException e ) {
		printf("JWQUIK[E] %s\n", e.what());
		return;
	}
	try {
		callback = JWQUIK_GET_CALLBACK(helper);
		method = helper->getMethodId
			(callback, "onConnectionStatus", "(JJLjava/lang/String;)V");
		helper->callVoidMethod_LLO(callback, method, (jlong)eventId,
			(jlong)errorCode, helper->toJstring(message));
	}catch ( JavaHelperException e ) {
		printf("JWQUIK[E] %s\n", e.what());
	}
	helper->drop();
}

void DriverCallbackTransfer::onTransactionReply
	(long result, long errorCode, const TransactionResult* tr)
{
	IJavaHelper* helper;
	jobject callback;
	jmethodID method;
	jobject jtr;
	try {
		helper = JavaWrapper::wrap(jvm);
	} catch ( JavaHelperException e ) {
		printf("JWQUIK[E] %s\n", e.what());
		return;
	}
	try {
		callback = JWQUIK_GET_CALLBACK(helper);
		method = helper->getMethodId(callback, "onTransactionReply",
			"(JJLru/prolib/JWQuik/ITransactionResult;)V");
		jtr = helper->createObject_LLDS
			("ru/prolib/JWQuik/Driver$TransactionResult",
			"(JJDLjava/lang/String;)V", tr->replyCode, tr->transId,
			tr->orderNumber, helper->toJstring(tr->resultMessage.c_str()));
		helper->callVoidMethod_LLO(callback, method, (jlong)result,
			(jlong)errorCode, jtr);
	} catch ( JavaHelperException e ) {
		printf("JWQUIK[E] %s\n", e.what());
	}
	helper->drop();
}

void DriverCallbackTransfer::onOrderStatus(long mode, IOrder* order) {
	IJavaHelper* helper;
	jobject callback;
	jmethodID method;
	jobject jorder;
	try {
		helper = JavaWrapper::wrap(jvm);
	} catch ( JavaHelperException e ) {
		printf("JWQUIK[E] %s\n", e.what());
		return;
	}
	try {
		callback = JWQUIK_GET_CALLBACK(helper);
		method = helper->getMethodId
			(callback, "onOrderStatus", "(JLru/prolib/JWQuik/IOrder;)V");
		jorder = helper->createObject_L
			(JWQUIK_ORDER_CLASS, "(J)V", (jlong)order);
		helper->callVoidMethod_LO(callback, method, (jlong)mode, jorder);
	} catch ( JavaHelperException e ) {
		printf("JWQUIK[E] %s\n", e.what());
	}
	helper->drop();
}

void DriverCallbackTransfer::onTradeStatus(long mode, ITrade* trade) {
	IJavaHelper* helper;
	jobject callback;
	jmethodID method;
	jobject jtrade;
	try {
		helper = JavaWrapper::wrap(jvm);
	} catch ( JavaHelperException e ) {
		printf("JWQUIK[E] %s\n", e.what());
		return;
	}
	try {
		callback = JWQUIK_GET_CALLBACK(helper);
		method = helper->getMethodId
			(callback, "onTradeStatus", "(JLru/prolib/JWQuik/ITrade;)V");
		jtrade = helper->createObject_L
			(JWQUIK_TRADE_CLASS, "(J)V", (jlong)trade);
		helper->callVoidMethod_LO(callback, method, (jlong)mode, jtrade);
	} catch ( JavaHelperException e ) {
		printf("JWQUIK[E] %s\n", e.what());
	}
	helper->drop();
}

} // end namespace jwquik
