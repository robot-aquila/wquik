#include "wquik/QuikCallbackAPI.h"

namespace wquik {

QuikCallbackAPI::QuikCallbackAPI(IDll* pLib) {
	//try {
		FNPI(pLib, CONNECTION_STATUS_CALLBACK);
		FNPI(pLib, ORDER_STATUS_CALLBACK);
		FNPI(pLib, TRADE_STATUS_CALLBACK);
		FNPI(pLib, TRANSACTION_REPLY_CALLBACK);
		FNPI(pLib, SET_HANDLER);
	//} catch ( LibraryException e ) {
		// TODO:
	//}
	lib = (IDll*)pLib->grab();
}

QuikCallbackAPI::~QuikCallbackAPI(void) {
	lib->drop();
}

TRANS2QUIK_TRANSACTION_REPLY_CALLBACK
	QuikCallbackAPI::getTransactionsReplyCallback()
{
	return (TRANS2QUIK_TRANSACTION_REPLY_CALLBACK)
		FNPA(TRANSACTION_REPLY_CALLBACK);
}

TRANS2QUIK_CONNECTION_STATUS_CALLBACK
	QuikCallbackAPI::getConnectionStatusCallback()
{
	return (TRANS2QUIK_CONNECTION_STATUS_CALLBACK)
		FNPA(CONNECTION_STATUS_CALLBACK);
}

TRANS2QUIK_ORDER_STATUS_CALLBACK
	QuikCallbackAPI::getOrderStatusCallback()
{
	return (TRANS2QUIK_ORDER_STATUS_CALLBACK)
		FNPA(ORDER_STATUS_CALLBACK);
}

TRANS2QUIK_TRADE_STATUS_CALLBACK
	QuikCallbackAPI::getTradeStatusCallback()
{
	return (TRANS2QUIK_TRADE_STATUS_CALLBACK)
		FNPA(TRADE_STATUS_CALLBACK);
}

void QuikCallbackAPI::setHandler(IQuikCallbackHandler* handler) {
	FNPA(SET_HANDLER)(handler);
}

} // end namespace wquik