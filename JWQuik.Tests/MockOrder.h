#pragma once
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "wquik/ITransactionDriver.h"

using namespace wquik;

class MockOrder : public IOrder {
public:
	virtual ~MockOrder(void){};

	MOCK_METHOD0(drop, bool());
	MOCK_METHOD0(grab, void*());

	MOCK_METHOD0(getQty, long());
	MOCK_METHOD0(getDate, long());
	MOCK_METHOD0(getTime, long());
	MOCK_METHOD0(getActivationTime, long());
	MOCK_METHOD0(getWithdrawTime, long());	
	MOCK_METHOD0(getExpiry, long());
	MOCK_METHOD0(getAccruedInt, double());
	MOCK_METHOD0(getYield, double());
	MOCK_METHOD0(getUID, long());
	MOCK_METHOD0(getUserId, const char*());
	MOCK_METHOD0(getAccount, const char*());
	MOCK_METHOD0(getBrokerRef, const char*());

	MOCK_METHOD0(getClientCode, const char*());
	MOCK_METHOD0(getFirmId, const char*());

	MOCK_METHOD0(getTransId, long());
	MOCK_METHOD0(getNumber, double());
	MOCK_METHOD0(getClassCode, const char*());
	MOCK_METHOD0(getSecCode, const char*());
	MOCK_METHOD0(getPrice, double());
	MOCK_METHOD0(getBalance, long());
	MOCK_METHOD0(getValue, double());
	MOCK_METHOD0(isSell, bool());
	MOCK_METHOD0(getStatus, long());
};
