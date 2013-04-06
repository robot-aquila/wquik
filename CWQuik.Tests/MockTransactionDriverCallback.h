#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "wquik/ITransactionDriver.h"

using namespace wquik;

class MockTransactionDriverCallback : public ITransactionDriverCallback {
public:
	virtual ~MockTransactionDriverCallback(void){};

	MOCK_METHOD3(onConnectionStatus, void
		(long eventId, long errorCode, const char* message));
	MOCK_METHOD3(onTransactionReply, void
		(long result, long errorCode, const TransactionResult* tr));
	MOCK_METHOD2(onOrderStatus, void(long mode, IOrder* order));
	MOCK_METHOD2(onTradeStatus, void(long mode, ITrade* trade));

};
