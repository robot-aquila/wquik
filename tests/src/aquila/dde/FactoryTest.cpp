/**
 * ============================================================================
 * 2011/08/06
 * $Id: FactoryTest.cpp 101 2011-08-11 18:37:57Z whirlwind $ Juno
 * ============================================================================
 */
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/core/auto_drop.h"
#include "aquila/core/MockWinApi.h"
#include "aquila/core/WinApi.h"
#include "aquila/dde/Factory.h"
#include "aquila/dde/MockCallbackHandler.h"
#include "aquila/dde/Instance.h"

using namespace testing;
using namespace aquila::core;

namespace aquila {
	namespace dde {

class FactoryTest : public ::testing::Test {
public:

	void SetUp() {
		WinApi::setInstance(&winApi);
	}

	void TearDown() {
		WinApi::setInstance(NULL);
	}

protected:
	MockWinApi winApi;
	MockCallbackHandler handler;

};

TEST_F(FactoryTest, testConstructor_WoArgs) {{
	auto_drop<Factory> f(new Factory());

	ASSERT_EQ(2, winApi.getRefCount());
}}

TEST_F(FactoryTest, testDestructorDecrementsRefCount_ConstructorWoArgs) {{
	Factory* f = new Factory();
	delete f;

	ASSERT_EQ(1, winApi.getRefCount());
}}

TEST_F(FactoryTest, testConstructor_WithArg) {{
	auto_drop<Factory> f(new Factory(&winApi));

	ASSERT_EQ(2, winApi.getRefCount());
}}

TEST_F(FactoryTest, testDestructorDecrementsRefCount_ConstructorWithArg) {{
	Factory* f = new Factory(&winApi);
	delete f;

	ASSERT_EQ(1, winApi.getRefCount());
}}

TEST_F(FactoryTest, testProduce) {{
	InSequence s;
	EXPECT_CALL(winApi, DdeInitialize(_, &Instance::CallbackFunction, 0, 0))
		.Times(1)
		.WillOnce(DoAll(SetArgumentPointee<0>(12345),Return(DMLERR_NO_ERROR)));
	EXPECT_CALL(winApi, DdeUninitialize(12345))
		.Times(1).
		WillOnce(Return(TRUE));

	auto_drop<Factory> f(new Factory(&winApi));
	auto_drop<IInstance> i(f->produce(&handler, CP_WINUNICODE));

	Instance* pInstance = (Instance*)i.get();
	ASSERT_EQ(&handler, pInstance->getCallbackHandler());
	ASSERT_EQ(&winApi, pInstance->getWinApi());
	ASSERT_EQ(3, winApi.getRefCount());
	ASSERT_EQ(CP_WINUNICODE, pInstance->getCodePage());
}}

	} // end namespace dde
} // end namespace aquila