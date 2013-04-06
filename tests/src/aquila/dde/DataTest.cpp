/**
 * ============================================================================
 * 2011/07/18
 * $Id: DataTest.cpp 101 2011-08-11 18:37:57Z whirlwind $ Juno
 * ============================================================================
 */
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/core/auto_drop.h"
#include "aquila/core/MockWinApi.h"
#include "aquila/dde/Data.h"
#include "aquila/dde/MockInstance.h"

using namespace testing;
using namespace aquila::core;

namespace aquila {
	namespace dde {

class DataTest : public ::testing::Test {
public:

	// Вспомогательная функция для тестирования Data::getData
	DWORD DdeGetData(HDDEDATA hData, LPBYTE pDst, DWORD cbMax, DWORD cbOff) {
		std::string str("zulu 19");
		strcpy_s((char*)pDst, cbMax, str.c_str());
		return str.size() + 1;
	}

protected:
	MockWinApi winApi;
	MockInstance instance;

};


TEST_F(DataTest, testConstruct) {
	HDDEDATA hData = (HDDEDATA)776655;
	auto_drop<IData> data(new Data(&instance, &winApi, hData));

	ASSERT_EQ(2, winApi.getRefCount());
	ASSERT_EQ(2, instance.getRefCount());
}


TEST_F(DataTest, testAccessors) {
	HDDEDATA hData = (HDDEDATA)11263;

	auto_drop<Data> data(new Data(&instance, &winApi, hData));

	ASSERT_EQ(&winApi, data->getWinApi());
	ASSERT_EQ(&instance, data->getInstance());
	ASSERT_EQ(hData, data->getHandle());
}


TEST_F(DataTest, testGetSize) {{
	InSequence s;
	HDDEDATA hData = (HDDEDATA)11223;
	
	EXPECT_CALL(winApi, DdeGetData(hData, NULL, 0, 0))
		.Times(1)
		.WillOnce(Return(15));

	auto_drop<Data> data(new Data(&instance, &winApi, hData));

	ASSERT_EQ(15, data->getSize());
}}


TEST_F(DataTest, testGetData) {{
	InSequence s;
	char buffer[256];
	memset(buffer, 0, sizeof(buffer));
	HDDEDATA hData = (HDDEDATA)88772;
		
	EXPECT_CALL(winApi, DdeGetData(hData, _, sizeof(buffer), 5))
		.Times(1)
		.WillOnce(Invoke(this, &DataTest::DdeGetData));

	auto_drop<Data> data(new Data(&instance, &winApi, hData));

	ASSERT_EQ(8, data->getData((LPBYTE)buffer, sizeof(buffer), 5));
	ASSERT_STREQ("zulu 19", buffer);
}}

	} // end namespace dde
} // end namespace aquila