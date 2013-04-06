#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string.h>
#include "wquik/Trade.h"
#include "MockTrans2QuikAPI.h"

using namespace testing;
using namespace wquik;

class TradeTest : public ::testing::Test {
protected:
	MockTrans2QuikAPI mock;
	Trade* trade;

	virtual void SetUp() {
		trade = new Trade(1111.44, 2222.55, "ERBR", "ROSN",
			250.03, 10, 2500.3, true, 12345, &mock);
	}

	virtual void TearDown() {
		trade->drop();
	}
};

TEST_F(TradeTest, testConstructor) {
	ASSERT_EQ(2, mock.getRefCount()); // trade grabs the api
}

TEST_F(TradeTest, testGetNumber) {
	ASSERT_EQ(1111.44, trade->getNumber());
}

TEST_F(TradeTest, testGetOrderNumber) {
	ASSERT_EQ(2222.55, trade->getOrderNumber());
}

TEST_F(TradeTest, testGetClassCode) {
	ASSERT_STREQ("ERBR", trade->getClassCode());
}

TEST_F(TradeTest, testGetSecCode) {
	ASSERT_STREQ("ROSN", trade->getSecCode());
}

TEST_F(TradeTest, testGetPrice) {
	ASSERT_EQ(250.03, trade->getPrice());
}

TEST_F(TradeTest, testGetQty) {
	ASSERT_EQ(10, trade->getQty());
}

TEST_F(TradeTest, testIsSell) {
	ASSERT_TRUE(trade->isSell());
}

TEST_F(TradeTest, testGetValue) {
	ASSERT_EQ(2500.3, trade->getValue());
}

TEST_F(TradeTest, testGetDate) {
	EXPECT_CALL(mock, TRADE_DATE(12345))
		.Times(AtLeast(1))
		.WillOnce(Return(100));
	ASSERT_EQ(100, trade->getDate());
}

TEST_F(TradeTest, testGetSettleDate) {
	EXPECT_CALL(mock, TRADE_SETTLE_DATE(12345))
		.Times(AtLeast(1))
		.WillOnce(Return(500));
	ASSERT_EQ(500, trade->getSettleDate());
}

TEST_F(TradeTest, testGetTime) {
	EXPECT_CALL(mock, TRADE_TIME(12345))
		.Times(AtLeast(1))
		.WillOnce(Return(666));
	ASSERT_EQ(666, trade->getTime());
}

TEST_F(TradeTest, testIsMarginal) {
	EXPECT_CALL(mock, TRADE_IS_MARGINAL(12345))
		.Times(AtLeast(1))
		.WillOnce(Return(1));
	ASSERT_TRUE(trade->isMarginal());
}

TEST_F(TradeTest, testGetAccruedInt) {
	EXPECT_CALL(mock, TRADE_ACCRUED_INT(12345))
		.Times(AtLeast(1))
		.WillOnce(Return(11.22));
	ASSERT_EQ(11.22, trade->getAccruedInt());
}

TEST_F(TradeTest, testGetYield) {
	EXPECT_CALL(mock, TRADE_YIELD(12345))
		.Times(AtLeast(1))
		.WillOnce(Return(33.44));
	ASSERT_EQ(33.44, trade->getYield());
}

TEST_F(TradeTest, testGetTsCommission) {
	EXPECT_CALL(mock, TRADE_TS_COMMISSION(12345))
		.Times(AtLeast(1))
		.WillOnce(Return(44.33));
	ASSERT_EQ(44.33, trade->getTsCommission());
}

TEST_F(TradeTest, testGetClearingCenterCommission) {
	EXPECT_CALL(mock, TRADE_CLEARING_CENTER_COMMISSION(12345))
		.Times(AtLeast(1))
		.WillOnce(Return(88.99));
	ASSERT_EQ(88.99, trade->getClearingCenterCommission());
}

TEST_F(TradeTest, testGetExchangeCommission) {
	EXPECT_CALL(mock, TRADE_EXCHANGE_COMMISSION(12345))
		.Times(AtLeast(1))
		.WillOnce(Return(77.66));
	ASSERT_EQ(77.66, trade->getExchangeCommission());
}

TEST_F(TradeTest, testGetTradingSystemCommission) {
	EXPECT_CALL(mock, TRADE_TRADING_SYSTEM_COMMISSION(12345))
		.Times(AtLeast(1))
		.WillOnce(Return(44.33));
	ASSERT_EQ(44.33, trade->getTradingSystemCommission());
}

TEST_F(TradeTest, testGetPrice2) {
	EXPECT_CALL(mock, TRADE_PRICE2(12345))
		.Times(AtLeast(1))
		.WillOnce(Return(42.12));
	ASSERT_EQ(42.12, trade->getPrice2());
}

TEST_F(TradeTest, testGetRepoRate) {
	EXPECT_CALL(mock, TRADE_REPO_RATE(12345))
		.Times(AtLeast(1))
		.WillOnce(Return(88.991));
	ASSERT_EQ(88.991, trade->getRepoRate());
}

TEST_F(TradeTest, testGetRepoValue) {
	EXPECT_CALL(mock, TRADE_REPO_VALUE(12345))
		.Times(AtLeast(1))
		.WillOnce(Return(88.22));
	ASSERT_EQ(88.22, trade->getRepoValue());
}

TEST_F(TradeTest, testGetRepo2Value) {
	EXPECT_CALL(mock, TRADE_REPO2_VALUE(12345))
		.Times(AtLeast(1))
		.WillOnce(Return(66.229));
	ASSERT_EQ(66.229, trade->getRepo2Value());
}

TEST_F(TradeTest, testGetAccruedInt2) {
	EXPECT_CALL(mock, TRADE_ACCRUED_INT2(12345))
		.Times(AtLeast(1))
		.WillOnce(Return(22.345));
	ASSERT_EQ(22.345, trade->getAccruedInt2());
}

TEST_F(TradeTest, testRepoTerm) {
	EXPECT_CALL(mock, TRADE_REPO_TERM(12345))
		.Times(AtLeast(1))
		.WillOnce(Return(12345));
	ASSERT_EQ(12345, trade->getRepoTerm());
}

TEST_F(TradeTest, testGetStartDiscount) {
	EXPECT_CALL(mock, TRADE_START_DISCOUNT(12345))
		.Times(AtLeast(1))
		.WillOnce(Return(14.56));
	ASSERT_EQ(14.56, trade->getStartDiscount());
}

TEST_F(TradeTest, testGetLowerDiscount) {
	EXPECT_CALL(mock, TRADE_LOWER_DISCOUNT(12345))
		.Times(AtLeast(1))
		.WillOnce(Return(54.321));
	ASSERT_EQ(54.321, trade->getLowerDiscount());
}

TEST_F(TradeTest, testGetUpperDiscount) {
	EXPECT_CALL(mock, TRADE_UPPER_DISCOUNT(12345))
		.Times(AtLeast(1))
		.WillOnce(Return(154.321));
	ASSERT_EQ(154.321, trade->getUpperDiscount());
}

TEST_F(TradeTest, testGetBlockSecurities) {
	EXPECT_CALL(mock, TRADE_BLOCK_SECURITIES(12345))
		.Times(AtLeast(1))
		.WillOnce(Return(777));
	ASSERT_EQ(777, trade->getBlockSecurities());
}

TEST_F(TradeTest, testGetCurrency) {
	EXPECT_CALL(mock, TRADE_CURRENCY(12345))
		.Times(AtLeast(1))
		.WillOnce(Return((char*)"ZUZUKA"));
	ASSERT_STREQ("ZUZUKA", trade->getCurrency());
}

TEST_F(TradeTest, testGetSettleCurrency) {
	EXPECT_CALL(mock, TRADE_SETTLE_CURRENCY(12345))
		.Times(AtLeast(1))
		.WillOnce(Return((char*)"KAKAKA"));
	ASSERT_STREQ("KAKAKA", trade->getSettleCurrency());
}

TEST_F(TradeTest, testGetSettleCode) {
	EXPECT_CALL(mock, TRADE_SETTLE_CODE(12345))
		.Times(AtLeast(1))
		.WillOnce(Return((char*)"TERKA"));
	ASSERT_STREQ("TERKA", trade->getSettleCode());
}

TEST_F(TradeTest, testGetAccount) {
	EXPECT_CALL(mock, TRADE_ACCOUNT(12345))
		.Times(AtLeast(1))
		.WillOnce(Return((char*)"ACCOUNT"));
	ASSERT_STREQ("ACCOUNT", trade->getAccount());
}

TEST_F(TradeTest, testGetBrokerRef) {
	EXPECT_CALL(mock, TRADE_BROKERREF(12345))
		.Times(AtLeast(1))
		.WillOnce(Return((char*)"BROKER"));
	ASSERT_STREQ("BROKER", trade->getBrokerRef());
}

TEST_F(TradeTest, testGetClientCode) {
	EXPECT_CALL(mock, TRADE_CLIENT_CODE(12345))
		.Times(AtLeast(1))
		.WillOnce(Return((char*)"CLIENT"));
	ASSERT_STREQ("CLIENT", trade->getClientCode());
}

TEST_F(TradeTest, testGetUserId) {
	EXPECT_CALL(mock, TRADE_USERID(12345))
		.Times(AtLeast(1))
		.WillOnce(Return((char*)"USER"));
	ASSERT_STREQ("USER", trade->getUserId());
}

TEST_F(TradeTest, testGetFirmId) {
	EXPECT_CALL(mock, TRADE_FIRMID(12345))
		.Times(AtLeast(1))
		.WillOnce(Return((char*)"FIRM"));
	ASSERT_STREQ("FIRM", trade->getFirmId());
}

TEST_F(TradeTest, testGetPartnerFirmId) {
	EXPECT_CALL(mock, TRADE_PARTNER_FIRMID(12345))
		.Times(AtLeast(1))
		.WillOnce(Return((char*)"PARTNER"));
	ASSERT_STREQ("PARTNER", trade->getPartnerFirmId());
}

TEST_F(TradeTest, testGetExchangeCode) {
	EXPECT_CALL(mock, TRADE_EXCHANGE_CODE(12345))
		.Times(AtLeast(1))
		.WillOnce(Return((char*)"EXCHANGE"));
	ASSERT_STREQ("EXCHANGE", trade->getExchangeCode());
}

TEST_F(TradeTest, testGetStationId) {
	EXPECT_CALL(mock, TRADE_STATION_ID(12345))
		.Times(AtLeast(1))
		.WillOnce(Return((char*)"STATION"));
	ASSERT_STREQ("STATION", trade->getStationId());
}
