#pragma once
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "wquik/ITransactionDriver.h"

using namespace wquik;

class MockTrade : public ITrade {
public:
	virtual ~MockTrade(void){};

	MOCK_METHOD0(drop, bool());
	MOCK_METHOD0(grab, void*());

	MOCK_METHOD0(getDate, long());
	MOCK_METHOD0(getSettleDate, long ());
	MOCK_METHOD0(getTime, long());
	MOCK_METHOD0(isMarginal, bool());
	MOCK_METHOD0(getAccruedInt, double());
	MOCK_METHOD0(getYield, double());
	MOCK_METHOD0(getTsCommission, double());
	MOCK_METHOD0(getClearingCenterCommission, double());
	MOCK_METHOD0(getExchangeCommission, double());
	MOCK_METHOD0(getTradingSystemCommission, double());
	MOCK_METHOD0(getPrice2, double());
	MOCK_METHOD0(getRepoRate, double());
	MOCK_METHOD0(getRepoValue, double());
	MOCK_METHOD0(getRepo2Value, double());
	MOCK_METHOD0(getAccruedInt2, double());
	MOCK_METHOD0(getRepoTerm, long());
	MOCK_METHOD0(getStartDiscount, double());
	MOCK_METHOD0(getLowerDiscount, double());
	MOCK_METHOD0(getUpperDiscount, double());
	MOCK_METHOD0(getBlockSecurities, long());
	MOCK_METHOD0(getCurrency, const char*());
	MOCK_METHOD0(getSettleCurrency, const char*());
	MOCK_METHOD0(getSettleCode, const char*());
	MOCK_METHOD0(getAccount, const char*());
	MOCK_METHOD0(getBrokerRef, const char*());
	MOCK_METHOD0(getClientCode, const char*());
	MOCK_METHOD0(getUserId, const char*());
	MOCK_METHOD0(getFirmId, const char*());
	MOCK_METHOD0(getPartnerFirmId, const char*());
	MOCK_METHOD0(getExchangeCode, const char*());
	MOCK_METHOD0(getStationId, const char*());

	MOCK_METHOD0(getNumber, double());
	MOCK_METHOD0(getOrderNumber, double());
	MOCK_METHOD0(getClassCode, const char*());
	MOCK_METHOD0(getSecCode, const char*());
	MOCK_METHOD0(getPrice, double());
	MOCK_METHOD0(getQty, long());
	MOCK_METHOD0(isSell, bool());
	MOCK_METHOD0(getValue, double());

};
