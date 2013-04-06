#pragma once
#include "jwquik/IDriverCallbackTransfer.h"

namespace jwquik {

class DriverCallbackTransfer : public IDriverCallbackTransfer {
public:
	virtual JWQUIKAPI ~DriverCallbackTransfer(void);
	JWQUIKAPI DriverCallbackTransfer
		(IJavaHelper* helper, ITransactionDriver* drv, jobject obj);
	virtual JWQUIKAPI ITransactionDriver* getDriver();
	virtual JWQUIKAPI void onConnectionStatus(long eventId, long errorCode,
		const char* message);
	virtual JWQUIKAPI void onTransactionReply(long result, long errorCode,
		const TransactionResult* tr);
	virtual JWQUIKAPI void onOrderStatus(long mode, IOrder* order);
	virtual JWQUIKAPI void onTradeStatus(long mode, ITrade* trade);
private:
	jobject instance;
	JavaVM* jvm;
	ITransactionDriver* driver;
};

} // end namespace jwquik
