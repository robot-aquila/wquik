#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string.h>
#include "wquik/Order.h"
#include "MockTrans2QuikAPI.h"

using namespace testing;
using namespace wquik;

class OrderTest : public ::testing::Test {
protected:
	MockTrans2QuikAPI mock;
	Order* order;

	virtual void SetUp() {
		order = new Order(54321, 1111.44, "ERBR", "ROSN",
			250.03, 10, 2500.3, true, 1, 12345, &mock);
	}

	virtual void TearDown() {
		order->drop();
	}
};

TEST_F(OrderTest, testConstructor) {
	ASSERT_EQ(2, mock.getRefCount()); // order grabs the api
}

TEST_F(OrderTest, testGetTransId) {
	ASSERT_EQ(54321, order->getTransId());
}

TEST_F(OrderTest, testGetNumber) {
	ASSERT_EQ(1111.44, order->getNumber());
}

TEST_F(OrderTest, testGetClassCode) {
	ASSERT_STREQ("ERBR", order->getClassCode());
}

TEST_F(OrderTest, testGetSecCode) {
	ASSERT_STREQ("ROSN", order->getSecCode());
}

TEST_F(OrderTest, testGetPrice) {
	ASSERT_EQ(250.03, order->getPrice());
}

TEST_F(OrderTest, testGetBalance) {
	ASSERT_EQ(10, order->getBalance());
}

TEST_F(OrderTest, testGetValue) {
	ASSERT_EQ(2500.3, order->getValue());
}

TEST_F(OrderTest, testGetValueReturnsZeroIfPriceIsZero) {
	order->drop();
	order = new Order(54321, 1111.44, "ERBR", "ROSN",
		0, 10, 2500.3, true, 1, 12345, &mock);
	ASSERT_EQ(0, order->getValue());
}

TEST_F(OrderTest, testIsSell) {
	ASSERT_TRUE(order->isSell());
}

TEST_F(OrderTest, testGetStatus) {
	ASSERT_EQ(1, order->getStatus());
}

TEST_F(OrderTest, testGetQty) {
	EXPECT_CALL(mock, ORDER_QTY(12345))
		.Times(AtLeast(1))
		.WillOnce(Return(100));
	ASSERT_EQ(100, order->getQty());
}

TEST_F(OrderTest, testGetDate) {
	EXPECT_CALL(mock, ORDER_DATE(12345))
		.Times(AtLeast(1))
		.WillOnce(Return(333));
	ASSERT_EQ(333, order->getDate());
}

TEST_F(OrderTest, testGetTime) {
	EXPECT_CALL(mock, ORDER_TIME(12345))
		.Times(AtLeast(1))
		.WillOnce(Return(555));
	ASSERT_EQ(555, order->getTime());
}

TEST_F(OrderTest, testGetActivationTime) {
	EXPECT_CALL(mock, ORDER_ACTIVATION_TIME(12345))
		.Times(AtLeast(1))
		.WillOnce(Return(777));
	ASSERT_EQ(777, order->getActivationTime());
}

TEST_F(OrderTest, testGetWithdrawTime) {
	EXPECT_CALL(mock, ORDER_WITHDRAW_TIME(12345))
		.Times(AtLeast(1))
		.WillOnce(Return(888));
	ASSERT_EQ(888, order->getWithdrawTime());
}

TEST_F(OrderTest, testGetExpiry) {
	EXPECT_CALL(mock, ORDER_EXPIRY(12345))
		.Times(AtLeast(1))
		.WillOnce(Return(999));
	ASSERT_EQ(999, order->getExpiry());
}

TEST_F(OrderTest, testGetAccruedInt) {
	EXPECT_CALL(mock, ORDER_ACCRUED_INT(12345))
		.Times(AtLeast(1))
		.WillOnce(Return(12.34));
	ASSERT_EQ(12.34, order->getAccruedInt());
}

TEST_F(OrderTest, testGetYield) {
	EXPECT_CALL(mock, ORDER_YIELD(12345))
		.Times(AtLeast(1))
		.WillOnce(Return(43.21));
	ASSERT_EQ(43.21, order->getYield());
}

TEST_F(OrderTest, testGetUID) {
	EXPECT_CALL(mock, ORDER_UID(12345))
		.Times(AtLeast(1))
		.WillOnce(Return(5544));
	ASSERT_EQ(5544, order->getUID());
}

TEST_F(OrderTest, testGetUserId) {
	EXPECT_CALL(mock, ORDER_USERID(12345))
		.Times(AtLeast(1))
		.WillOnce(Return((char*)"ZUZUBABA"));
	ASSERT_STREQ("ZUZUBABA", order->getUserId());
}

TEST_F(OrderTest, testGetAccount) {
	EXPECT_CALL(mock, ORDER_ACCOUNT(12345))
		.Times(AtLeast(1))
		.WillOnce(Return((char*)"LP01-111"));
	ASSERT_STREQ("LP01-111", order->getAccount());
}

TEST_F(OrderTest, testGetBrokerRef) {
	EXPECT_CALL(mock, ORDER_BROKERREF(12345))
		.Times(AtLeast(1))
		.WillOnce(Return((char*)"ZZZ"));
	ASSERT_STREQ("ZZZ", order->getBrokerRef());
}

TEST_F(OrderTest, testGetClientCode) {
	EXPECT_CALL(mock, ORDER_CLIENT_CODE(12345))
		.Times(AtLeast(1))
		.WillOnce(Return((char*)"CLIENT"));
	ASSERT_STREQ("CLIENT", order->getClientCode());
}

TEST_F(OrderTest, testGetFirmId) {
	EXPECT_CALL(mock, ORDER_FIRMID(12345))
		.Times(AtLeast(1))
		.WillOnce(Return((char*)"FIRM"));
	ASSERT_STREQ("FIRM", order->getFirmId());
}

