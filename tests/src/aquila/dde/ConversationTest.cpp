/**
 * ============================================================================
 * 2011/07/18
 * $Id: ConversationTest.cpp 189 2012-01-30 16:03:21Z whirlwind $ Juno
 * ============================================================================
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/core/auto_drop.h"
#include "aquila/core/MockWinApi.h"
#include "aquila/dde/Conversation.h"
#include "aquila/dde/MockInstance.h"
#include "aquila/dde/MockString.h"

using namespace testing;

namespace aquila {
	namespace dde {

class ConversationTest : public ::testing::Test {
protected:
	MockWinApi winApi;
	MockInstance instance;
	MockString str;

public:
	/**
	 * Вспомогательный метод для тестирования
	 *	Conversation::getServiceName
	 *	Conversation::getTopic
	 */
	UINT DdeQueryConvInfo(HCONV hConv, DWORD idTrans, PCONVINFO pConvInfo) {
		pConvInfo->hszServiceReq = (HSZ)12345;
		pConvInfo->hszTopic = (HSZ)23456;
		return sizeof(CONVINFO);
	}

};

TEST_F(ConversationTest, testAccessors) {
	HCONV hConv = (HCONV)776655;

	auto_drop<Conversation> conv(new Conversation(&instance, &winApi, hConv));

	ASSERT_EQ(&winApi, conv->getWinApi());
	ASSERT_EQ(&instance, conv->getInstance());
	ASSERT_EQ(hConv, conv->getHandle());
}

TEST_F(ConversationTest, testGetServiceName) {{
	InSequence s;
	HCONV hConv = (HCONV)776655;
	auto_drop<Conversation> conv(new Conversation(&instance, &winApi, hConv));
	EXPECT_CALL(winApi, DdeQueryConvInfo(hConv, QID_SYNC,
			Pointee(Field(&CONVINFO::cb, sizeof(CONVINFO)))))
		.Times(1)
		.WillOnce(Invoke(this, &ConversationTest::DdeQueryConvInfo));
	EXPECT_CALL(instance, wrapString((HSZ)12345))
		.Times(1)
		.WillOnce(Return(&str));
	EXPECT_CALL(str, getString())
		.Times(1)
		.WillOnce(Return("service name"));

	str.grab(); // после использования, метод должен дропать полученный
			  // экземпляр строки

	ASSERT_STREQ("service name", conv->getServiceName().c_str());
	ASSERT_EQ(1, str.getRefCount());
}}

TEST_F(ConversationTest, testGetTopic) {{
	InSequence s;
	HCONV hConv = (HCONV)667722;
	auto_drop<Conversation> conv(new Conversation(&instance, &winApi, hConv));
	EXPECT_CALL(winApi, DdeQueryConvInfo(hConv, QID_SYNC,
			Pointee(Field(&CONVINFO::cb, sizeof(CONVINFO)))))
		.Times(1)
		.WillOnce(Invoke(this, &ConversationTest::DdeQueryConvInfo));
	EXPECT_CALL(instance, wrapString((HSZ)23456))
		.Times(1)
		.WillOnce(Return(&str));
	EXPECT_CALL(str, getString())
		.Times(1)
		.WillOnce(Return("topic"));

	str.grab();

	ASSERT_STREQ("topic", conv->getTopic().c_str());
	ASSERT_EQ(1, str.getRefCount());
}}

	} // end namespace dde
} // end namespace aquila