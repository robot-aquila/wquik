/**
 * ============================================================================
 * 2011/08/01
 * $Id: HelperWindowHandlerTest.cpp 104 2011-08-15 09:47:48Z whirlwind $ Juno
 * ============================================================================
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/core/auto_drop.h"
#include "aquila/ddesvr/HelperWindowHandler.h"
#include "aquila/ddesvr/MockServiceMap.h"
#include "aquila/dde/MockFactory.h"
#include "aquila/dde/MockInstance.h"
#include "aquila/dde/MockCallbackHandler.h"
#include "aquila/dde/MockString.h"

using namespace testing;
using namespace aquila::core;
using namespace aquila::dde;

namespace aquila {
	namespace ddesvr {

class HelperWindowHandlerTest : public ::testing::Test {
public:


protected:
	MockString str;
	MockServiceMap sm;
	MockInstance instance;
	MockCallbackHandler handler;
	MockFactory factory;
};


TEST_F(HelperWindowHandlerTest, testConstructorIncrementsRefCount) {{
	auto_drop<HelperWindowHandler> h
		(new HelperWindowHandler(&factory, &sm, &handler));
	ASSERT_EQ(2, factory.getRefCount());
	ASSERT_EQ(2, sm.getRefCount());
	ASSERT_EQ(2, handler.getRefCount());
}}

TEST_F(HelperWindowHandlerTest, testDestructorDecrementsRefCount) {{
	HelperWindowHandler* h = new HelperWindowHandler(&factory, &sm, &handler);
	delete h;
	ASSERT_EQ(1, factory.getRefCount());
	ASSERT_EQ(1, sm.getRefCount());
	ASSERT_EQ(1, handler.getRefCount());
}}

TEST_F(HelperWindowHandlerTest, testAccessors) {{
	auto_drop<HelperWindowHandler> h
		(new HelperWindowHandler(&factory, &sm, &handler));
	ASSERT_EQ(&factory, h->getInstanceFactory());
	ASSERT_EQ(&sm, h->getServiceMap());
	ASSERT_EQ(&handler, h->getCallbackHandler());
	ASSERT_EQ(NULL, h->getInstance()); // test method
}}

TEST_F(HelperWindowHandlerTest, testDestructorDropsInstanceIfExists) {{
	instance.grab();
	HelperWindowHandler* h = new HelperWindowHandler(&factory, &sm, &handler);
	h->setInstance(&instance);
	delete h;
	ASSERT_EQ(1, instance.getRefCount());
}}

TEST_F(HelperWindowHandlerTest, testOnBeforeCreate) {{
	InSequence s;
	auto_drop<HelperWindowHandler> h
		(new HelperWindowHandler(&factory, &sm, &handler));
	EXPECT_CALL(factory, produce(&handler, CP_WINANSI))
		.Times(1)
		.WillOnce(Return(&instance));

	h->onBeforeCreate();
	ASSERT_EQ(&instance, h->getInstance());

	// сброс, что бы не дропал
	h->setInstance(NULL);
}}

TEST_F(HelperWindowHandlerTest, testOnCreate) {{
	InSequence s;
	auto_drop<HelperWindowHandler> h
		(new HelperWindowHandler(&factory, &sm, &handler));

	// ниче не делает
	h->onCreate();
}}

TEST_F(HelperWindowHandlerTest, testOnDestroy) {{
	InSequence s;
	auto_drop<HelperWindowHandler> h
		(new HelperWindowHandler(&factory, &sm, &handler));

	// пока ниче не делает
	h->onDestroy();
}}

TEST_F(HelperWindowHandlerTest, testOnAfterDestroy) {{
	InSequence s;
	auto_drop<HelperWindowHandler> h
		(new HelperWindowHandler(&factory, &sm, &handler));

	instance.grab();
	h->setInstance(&instance);

	h->onAfterDestroy();

	ASSERT_EQ(1, instance.getRefCount());
	ASSERT_EQ(NULL, h->getInstance());
}}

TEST_F(HelperWindowHandlerTest, testOnRegisterService) {{
	InSequence s;
	auto_drop<HelperWindowHandler> h
		(new HelperWindowHandler(&factory, &sm, &handler));
	instance.grab();
	h->setInstance(&instance);
	EXPECT_CALL(sm, getName(123))
		.Times(1)
		.WillOnce(Return("zulu4"));
	EXPECT_CALL(instance, createString(StrEq("zulu4")))
		.Times(1)
		.WillOnce(Return(&str));
	str.grab(); // должен дропнуть строку
	EXPECT_CALL(instance, nameService(&str, DNS_REGISTER))
		.Times(1);

	h->onRegisterService(123);
	ASSERT_EQ(1, str.getRefCount());
}}

TEST_F(HelperWindowHandlerTest, testOnUnregisterService) {{
	InSequence s;
	auto_drop<HelperWindowHandler> h
		(new HelperWindowHandler(&factory, &sm, &handler));
	instance.grab();
	h->setInstance(&instance);
	EXPECT_CALL(sm, getName(123))
		.Times(1)
		.WillOnce(Return("foobar"));
	EXPECT_CALL(instance, createString(StrEq("foobar")))
		.Times(1)
		.WillOnce(Return(&str));
	str.grab(); // должен дропнуть строку
	EXPECT_CALL(instance, nameService(&str, DNS_UNREGISTER))
		.Times(1);

	h->onUnregisterService(123);
	ASSERT_EQ(1, str.getRefCount());
}}


	} // end namespace ddesvr
} // end namespace aquila