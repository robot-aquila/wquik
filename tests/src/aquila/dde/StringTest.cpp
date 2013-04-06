/**
 * ============================================================================
 * 2011/07/18
 * $Id: StringTest.cpp 101 2011-08-11 18:37:57Z whirlwind $
 * Juno
 * ============================================================================
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/core/MockWinApi.h"
#include "aquila/core/auto_drop.h"
#include "aquila/dde/String.h"
#include "aquila/dde/MockInstance.h"

using namespace testing;
using namespace aquila::core;

namespace aquila {
	namespace dde {

class StringTest : public ::testing::Test {
public:

	/**
	 * Вспомогательная функция для тестирования String::getString.
	 */
	DWORD DdeQueryString(DWORD idInst, HSZ hsz, char* psz, DWORD cchMax,
		int iCodePage)
	{
		std::string str("foobar test");
		strcpy_s(psz, cchMax, str.c_str());
		return str.size();
	}

	/**
	 * Ожидать вызовов создания winApi-строки.
	 *
	 * dwInstanceId - ожидаемый идентификатор инстанса winApi,
	 * hStr - ожидаемый дескриптор строки,
	 * iCodePage - ожидаемая кодировка,
	 * expectedStr - ожидаемая исходная строка
	 */
	void EXPECT_CREATE_DDE_STRING(DWORD dwInstanceId, HSZ hStr, int iCodePage,
		const char* expectedStr)
	{
		EXPECT_CALL(instance, getId())
			.Times(1)
			.WillOnce(Return(dwInstanceId));
		EXPECT_CALL(winApi, DdeCreateStringHandle(dwInstanceId,
				StrEq(expectedStr), iCodePage))
			.Times(1)
			.WillOnce(Return(hStr));
	}

	/**
	 * Ожидать вызовов освобождения winApi-строки.
	 *
	 * dwInstanceId - ожидаемый идентификатор инстанса winApi,
	 * hStr - ожидаемый дескриптор строки
	 */
	void EXPECT_FREE_DDE_STRING(DWORD dwInstanceId, HSZ hStr) {
		EXPECT_CALL(instance, getId())
			.Times(1)
			.WillOnce(Return(dwInstanceId));
		EXPECT_CALL(winApi, DdeFreeStringHandle(dwInstanceId, hStr))
			.Times(1);
	}

protected:
	MockWinApi winApi;
	MockInstance instance;

};


TEST_F(StringTest, testConstructDestruct_Hsz) {
	auto_drop<IString> string
		(new String(&instance, &winApi, (HSZ)12345, CP_WINANSI));

	ASSERT_EQ(2, instance.getRefCount());
	ASSERT_EQ(2, winApi.getRefCount());
}

TEST_F(StringTest, testConstructDestruct_String) {{
	InSequence s;
	DWORD dwInstanceId = 12345;
	HSZ hStr = (HSZ)54321;
	
	EXPECT_CREATE_DDE_STRING(dwInstanceId, hStr, CP_WINANSI, "foobar");
	EXPECT_FREE_DDE_STRING(dwInstanceId, hStr);


	auto_drop<IString> string
		(new String(&instance, &winApi, "foobar", CP_WINANSI));

	ASSERT_EQ(hStr, string->getHandle());
	ASSERT_EQ(2, instance.getRefCount());
	ASSERT_EQ(2, winApi.getRefCount());
}}


TEST_F(StringTest, testGetString) {{
	InSequence s;
	DWORD dwInstanceId = 12345;
	HSZ hStr = (HSZ)54321;

	EXPECT_CALL(instance, getId())
		.Times(1)
		.WillOnce(Return(dwInstanceId));
	EXPECT_CALL(winApi, DdeQueryString(dwInstanceId, hStr, _, 256, CP_WINANSI))
		.Times(1)
		.WillOnce(Invoke(this, &StringTest::DdeQueryString));

	auto_drop<IString> string
		(new String(&instance, &winApi, hStr, CP_WINANSI));

	ASSERT_EQ("foobar test", string->getString());
}}


TEST_F(StringTest, testGetHandle_Hsz) {
	HSZ hStr = (HSZ)88776;

	auto_drop<IString> string
		(new String(&instance, &winApi, hStr, CP_WINANSI));

	ASSERT_EQ(hStr, string->getHandle());
}


TEST_F(StringTest, testGetHandle_String) {{
	InSequence s;
	DWORD dwInstanceId = 12345;
	HSZ hStr = (HSZ)54321;
		
	EXPECT_CREATE_DDE_STRING(dwInstanceId, hStr, CP_WINUNICODE, "zulu4");
	EXPECT_FREE_DDE_STRING(dwInstanceId, hStr);

	auto_drop<IString> string
		(new String(&instance, &winApi, "zulu4", CP_WINUNICODE));

	ASSERT_EQ(hStr, string->getHandle());
}}


TEST_F(StringTest, testGetCodePage_Hsz) {
	auto_drop<IString> string1
		(new String(&instance, &winApi, (HSZ)12345, CP_WINUNICODE));
	auto_drop<IString> string2
		(new String(&instance, &winApi, (HSZ)12222, CP_WINANSI));

	ASSERT_EQ(CP_WINUNICODE, string1->getCodePage());
	ASSERT_EQ(CP_WINANSI, string2->getCodePage());
}


TEST_F(StringTest, testGetCodePage_String) {{
	InSequence s;
	DWORD dwInstanceId = 12345;
	HSZ hStr1 = (HSZ)54321;
	HSZ hStr2 = (HSZ)88888;
		
	EXPECT_CREATE_DDE_STRING(dwInstanceId, hStr1, CP_WINUNICODE, "zulu4");
	EXPECT_CREATE_DDE_STRING(dwInstanceId, hStr2, CP_WINANSI, "foobar");

	EXPECT_FREE_DDE_STRING(dwInstanceId, hStr2);
	EXPECT_FREE_DDE_STRING(dwInstanceId, hStr1);

	auto_drop<IString> string1
		(new String(&instance, &winApi, "zulu4", CP_WINUNICODE));
	auto_drop<IString> string2
		(new String(&instance, &winApi, "foobar", CP_WINANSI));

	ASSERT_EQ(CP_WINUNICODE, string1->getCodePage());
	ASSERT_EQ(CP_WINANSI, string2->getCodePage());
}}


TEST_F(StringTest, testDestructor_FreesObjects) {
	IString* pStr = new String(&instance, &winApi, (HSZ)12345, CP_WINANSI);
	pStr->drop();

	ASSERT_EQ(1, winApi.getRefCount());
	ASSERT_EQ(1, instance.getRefCount());
}

TEST_F(StringTest, testAccessors) {
	auto_drop<String> string
		(new String(&instance, &winApi, (HSZ)22222, CP_WINANSI));

	ASSERT_EQ(&instance, string->getInstance());
	ASSERT_EQ(&winApi, string->getWinApi());
}

	} // end namespace dde
} // end namespace aquila
