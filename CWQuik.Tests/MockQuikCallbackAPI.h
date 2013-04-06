#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "wquik/IQuikCallbackAPI.h"

using namespace wquik;

class MockQuikCallbackAPI : public IQuikCallbackAPI {
public:
	virtual ~MockQuikCallbackAPI(void){};

	MOCK_METHOD0(getTransactionsReplyCallback, TRANS2QUIK_TRANSACTION_REPLY_CALLBACK());
	MOCK_METHOD0(getConnectionStatusCallback, TRANS2QUIK_CONNECTION_STATUS_CALLBACK());
	MOCK_METHOD0(getOrderStatusCallback, TRANS2QUIK_ORDER_STATUS_CALLBACK());
	MOCK_METHOD0(getTradeStatusCallback, TRANS2QUIK_TRADE_STATUS_CALLBACK());
	MOCK_METHOD1(setHandler, void(IQuikCallbackHandler*));
};
