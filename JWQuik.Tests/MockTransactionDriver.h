#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "wquik/ITransactionDriver.h"

using namespace wquik;

class MockTransactionDriver : public ITransactionDriver {
public:
	virtual ~MockTransactionDriver(void){};

	MOCK_METHOD0(grab, void*());
	MOCK_METHOD0(drop, bool());

	MOCK_METHOD0(setAsyncMode, void());
	MOCK_METHOD0(setSyncMode, void());
	MOCK_METHOD0(isSyncMode, bool());
	MOCK_METHOD0(isAsyncMode, bool());
	MOCK_METHOD1(connect, void(const char*));
	MOCK_METHOD0(disconnect, void());
	MOCK_METHOD0(isQuikConnected, bool());
	MOCK_METHOD0(isDllConnected, bool());
	MOCK_METHOD2(sendSyncTransaction, void(const char*,TransactionResult* tr));
	MOCK_METHOD1(sendAsyncTransaction, void(const char*));
	MOCK_METHOD1(setCallbackHandler, void(ITransactionDriverCallback*));

};
