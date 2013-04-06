/**
 * ============================================================================
 * 2011/08/01
 * $Id: CallbackDispatcherTest.cpp 190 2012-01-30 18:34:54Z whirlwind $ Juno
 * ============================================================================
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/core/auto_drop.h"
#include "aquila/core/MockEvent.h"
#include "aquila/ddesvr/CallbackDispatcher.h"
#include "aquila/ddesvr/MockServiceMap.h"
#include "aquila/dde/MockInstance.h"
#include "aquila/dde/MockString.h"
#include "aquila/dde/MockCallbackHandler.h"
#include "aquila/dde/MockConversation.h"
#include "aquila/dde/MockData.h"

using namespace testing;
using namespace aquila::core;

namespace aquila {
	namespace ddesvr {

class CallbackDispatcherTest : public ::testing::Test {
public:


protected:
	MockEvent e;
	MockServiceMap sm;
	MockString s1;
	MockString s2;
	MockData data;
	MockInstance instance;
	MockCallbackHandler handler;
	MockConversation conv;

};

TEST_F(CallbackDispatcherTest, testConstructorIncrementsRefCount) {{
	auto_drop<CallbackDispatcher> cd(new CallbackDispatcher(&sm, &e));
	ASSERT_EQ(2, sm.getRefCount());
	ASSERT_EQ(2, e.getRefCount());
}}

TEST_F(CallbackDispatcherTest, testDestructorDecrementsRefCount) {{
	CallbackDispatcher* cd = new CallbackDispatcher(&sm, &e);
	delete cd;
	ASSERT_EQ(1, sm.getRefCount());
	ASSERT_EQ(1, e.getRefCount());
}}

TEST_F(CallbackDispatcherTest, testAccessors) {{
	auto_drop<CallbackDispatcher> cd(new CallbackDispatcher(&sm, &e));
	ASSERT_EQ(&sm, cd->getServiceMap());
	ASSERT_EQ(&e, cd->getEvent());
}}

TEST_F(CallbackDispatcherTest, testOnConnect_Ok) {{
	auto_drop<CallbackDispatcher> cd(new CallbackDispatcher(&sm, &e));
	InSequence s;
	EXPECT_CALL(s2, getString())
		.Times(1)
		.WillOnce(Return("service name"));
	EXPECT_CALL(sm, has(Matcher<string>("service name")))
		.Times(1)
		.WillOnce(Return(true));
	EXPECT_CALL(sm, get(Matcher<string>("service name")))
		.Times(1)
		.WillOnce(Return(&handler));
	EXPECT_CALL(handler, onConnect(&s1, &s2, (PCONVCONTEXT)543, false))
		.Times(1)
		.WillOnce(Return(false));

	ASSERT_FALSE(cd->onConnect(&s1, &s2, (PCONVCONTEXT)543, false));
}}

TEST_F(CallbackDispatcherTest, testOnConnect_IgnoreIfNoService) {{
	auto_drop<CallbackDispatcher> cd(new CallbackDispatcher(&sm, &e));
	InSequence s;
	EXPECT_CALL(s2, getString())
		.Times(1)
		.WillOnce(Return("unknown service"));
	EXPECT_CALL(sm, has(Matcher<string>("unknown service")))
		.Times(1)
		.WillOnce(Return(false));

	ASSERT_FALSE(cd->onConnect(&s1, &s2, (PCONVCONTEXT)222, false));
	
}}

TEST_F(CallbackDispatcherTest, testOnConnectConfirm_Ok) {{
	auto_drop<CallbackDispatcher> cd(new CallbackDispatcher(&sm, &e));
	InSequence s;
	EXPECT_CALL(s2, getString())
		.Times(1)
		.WillOnce(Return("dde"));
	EXPECT_CALL(sm, has(Matcher<string>("dde")))
		.Times(1)
		.WillOnce(Return(true));
	EXPECT_CALL(sm, get(Matcher<string>("dde")))
		.Times(1)
		.WillOnce(Return(&handler));
	EXPECT_CALL(handler, onConnectConfirm(&conv, &s1, &s2, true))
		.Times(1);

	cd->onConnectConfirm(&conv, &s1, &s2, true);
}}

TEST_F(CallbackDispatcherTest, testOnConnectConfirm_IgnoreIfNoService) {{
	auto_drop<CallbackDispatcher> cd(new CallbackDispatcher(&sm, &e));
	InSequence s;
	EXPECT_CALL(s2, getString())
		.Times(1)
		.WillOnce(Return("zulu4"));
	EXPECT_CALL(sm, has(Matcher<string>("zulu4")))
		.Times(1)
		.WillOnce(Return(false));

	cd->onConnectConfirm(&conv, &s1, &s2, true);
}}


TEST_F(CallbackDispatcherTest, testOnDisconnect_Ok) {{
	auto_drop<CallbackDispatcher> cd(new CallbackDispatcher(&sm, &e));
	InSequence s;
	EXPECT_CALL(conv, getServiceName())
		.Times(1)
		.WillOnce(Return("test"));
	EXPECT_CALL(sm, has(Matcher<string>("test")))
		.Times(1)
		.WillOnce(Return(true));
	EXPECT_CALL(sm, get(Matcher<string>("test")))
		.Times(1)
		.WillOnce(Return(&handler));
	EXPECT_CALL(handler, onDisconnect(&conv, false))
		.Times(1);

	cd->onDisconnect(&conv, false);
}}

TEST_F(CallbackDispatcherTest, testOnDisconnect_IgnoreIfNoService) {{
	auto_drop<CallbackDispatcher> cd(new CallbackDispatcher(&sm, &e));
	InSequence s;
	EXPECT_CALL(conv, getServiceName())
		.Times(1)
		.WillOnce(Return("test2"));
	EXPECT_CALL(sm, has(Matcher<string>("test2")))
		.Times(1)
		.WillOnce(Return(false));

	cd->onDisconnect(&conv, false);
}}


TEST_F(CallbackDispatcherTest, testOnPoke_Ok) {{
	auto_drop<CallbackDispatcher> cd(new CallbackDispatcher(&sm, &e));
	InSequence s;
	EXPECT_CALL(conv, getServiceName())
		.Times(1)
		.WillOnce(Return("foo"));
	EXPECT_CALL(sm, has(Matcher<string>("foo")))
		.Times(1)
		.WillOnce(Return(true));
	EXPECT_CALL(sm, get(Matcher<string>("foo")))
		.Times(1)
		.WillOnce(Return(&handler));
	EXPECT_CALL(handler, onPoke(123, &conv, &s1, &s2, &data))
		.Times(1)
		.WillOnce(Return(DDE_FBUSY));

	ASSERT_EQ(DDE_FBUSY, cd->onPoke(123, &conv, &s1, &s2, &data));
}}

TEST_F(CallbackDispatcherTest, testOnPoke_IgnoreIfNoService) {{
	auto_drop<CallbackDispatcher> cd(new CallbackDispatcher(&sm, &e));
	InSequence s;
	EXPECT_CALL(conv, getServiceName())
		.Times(1)
		.WillOnce(Return("bar"));
	EXPECT_CALL(sm, has(Matcher<string>("bar")))
		.Times(1)
		.WillOnce(Return(false));

	ASSERT_EQ(DDE_FACK, cd->onPoke(123, &conv, &s1, &s2, &data));
}}

TEST_F(CallbackDispatcherTest, testOnRegister_Ok) {{
	auto_drop<CallbackDispatcher> cd(new CallbackDispatcher(&sm, &e));
	InSequence s;
	EXPECT_CALL(s1, getString())
		.Times(1)
		.WillOnce(Return("bar12"));
	EXPECT_CALL(sm, has(Matcher<string>("bar12")))
		.Times(1)
		.WillOnce(Return(true));
	EXPECT_CALL(sm, get(Matcher<string>("bar12")))
		.Times(1)
		.WillOnce(Return(&handler));
	EXPECT_CALL(handler, onRegister(&s1, &s2)).Times(1);
	EXPECT_CALL(e, set()).Times(1);

	cd->onRegister(&s1, &s2);
}}

TEST_F(CallbackDispatcherTest, testOnRegister_IgnoreIfNoService) {{
	auto_drop<CallbackDispatcher> cd(new CallbackDispatcher(&sm, &e));
	InSequence s;
	EXPECT_CALL(s1, getString())
		.Times(1)
		.WillOnce(Return("bar13"));
	EXPECT_CALL(sm, has(Matcher<string>("bar13")))
		.Times(1)
		.WillOnce(Return(false));

	cd->onRegister(&s1, &s2);
}}


TEST_F(CallbackDispatcherTest, testOnUnregister_Ok) {{
	auto_drop<CallbackDispatcher> cd(new CallbackDispatcher(&sm, &e));
	InSequence s;
	EXPECT_CALL(s1, getString())
		.Times(1)
		.WillOnce(Return("zulu4"));
	EXPECT_CALL(sm, has(Matcher<string>("zulu4")))
		.Times(1)
		.WillOnce(Return(true));
	EXPECT_CALL(sm, get(Matcher<string>("zulu4")))
		.Times(1)
		.WillOnce(Return(&handler));
	EXPECT_CALL(handler, onUnregister(&s1, &s2))
		.Times(1);
	EXPECT_CALL(sm, remove(Matcher<string>("zulu4")))
		.Times(1);
	EXPECT_CALL(e, set()).Times(1);

	cd->onUnregister(&s1, &s2);
}}

TEST_F(CallbackDispatcherTest, testOnUnregister_IgnoreIfNoService) {{
	auto_drop<CallbackDispatcher> cd(new CallbackDispatcher(&sm, &e));
	InSequence s;
	EXPECT_CALL(s1, getString())
		.Times(1)
		.WillOnce(Return("zulu4"));
	EXPECT_CALL(sm, has(Matcher<string>("zulu4")))
		.Times(1)
		.WillOnce(Return(false));

	cd->onUnregister(&s1, &s2);
}}


	} // end namespace ddesvr
} // end namespace aquila