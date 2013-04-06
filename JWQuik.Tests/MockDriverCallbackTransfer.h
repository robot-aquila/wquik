#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "jwquik/IDriverCallbackTransfer.h"

using namespace wquik;

class MockDriverCallbackTransfer : public IDriverCallbackTransfer {
public:
	virtual ~MockDriverCallbackTransfer(void){};

	MOCK_METHOD0(grab, void*());
	MOCK_METHOD0(drop, bool());

	MOCK_METHOD0(getDriver, ITransactionDriver*());
	MOCK_METHOD3(onConnectionStatus, void(long, long, const char*));
	MOCK_METHOD3(onTransactionReply, void(long result, long errorCode,
		const TransactionResult* tr));
	MOCK_METHOD2(onOrderStatus, void(long mode, IOrder* order));
	MOCK_METHOD2(onTradeStatus, void(long mode, ITrade* trade));
};
