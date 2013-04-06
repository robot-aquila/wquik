/**
 * ============================================================================
 * 2011/07/18
 * $Id: InstanceTest.cpp 101 2011-08-11 18:37:57Z whirlwind $ Juno
 * ============================================================================
 */
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/core/MockWinApi.h"
#include "aquila/core/auto_drop.h"
#include "aquila/dde/Instance.h"
#include "aquila/dde/MockCallbackHandler.h"
#include "aquila/dde/String.h"
#include "aquila/dde/macros.h"

using namespace testing;

namespace aquila {
	namespace dde {

class InstanceTest : public ::testing::Test {
public:


	// ���������� �������� ������ ������������� DDE ��������
	void EXPECT_INITIALIZE() {
		EXPECT_CALL(winApi, DdeInitialize(_, &Instance::CallbackFunction, 0, 0))
			.Times(1)
			.WillOnce(DoAll(
				SetArgumentPointee<0>(12345),
				Return(DMLERR_NO_ERROR)
			));
	}

	// ���������� �������� ������ ��������������� �������� DDE
	void EXPECT_UNINITIALIZE() {
		EXPECT_CALL(winApi, DdeUninitialize(12345))
			.Times(1)
			.WillOnce(Return(TRUE));
	}

protected:
	MockWinApi winApi;
	MockCallbackHandler callback;
};


// ���� ������������
TEST_F(InstanceTest, testConstruct_Ok) {{
	InSequence s;
	EXPECT_INITIALIZE();
	EXPECT_UNINITIALIZE();

	auto_drop<Instance> instance(new Instance(&winApi, &callback, CP_WINANSI));

	ASSERT_EQ(2, winApi.getRefCount());
	ASSERT_EQ(2, callback.getRefCount());
	ASSERT_EQ(1, instance->getRefCount());
}}

// ����������� ����������� ����������, ���� ��������� ���������������� DDE
TEST_F(InstanceTest, testConstruct_ThrowsIfInitializeFailed) {{
	EXPECT_CALL(winApi, DdeInitialize(_, &Instance::CallbackFunction, 0, 0))
		.Times(1)
		.WillOnce(DoAll(
			SetArgumentPointee<0>(12345),
			Return(DMLERR_INVALIDPARAMETER)
		));

	ASSERT_THROW(
		auto_drop<Instance>
			instance(new Instance(&winApi, &callback, CP_WINANSI)),
		std::exception);
}}

// ����������� ����������� ���������� ��� ������� ��������������
// ����� ������ ����������
TEST_F(InstanceTest, testConstruct_ThrowsIfInstanceAlreadyCreated) {{
	InSequence s;
	EXPECT_INITIALIZE();
	EXPECT_UNINITIALIZE();

	auto_drop<Instance> instance1
		(new Instance(&winApi, &callback, CP_WINANSI));

	ASSERT_THROW(auto_drop<Instance>
			instance2(new Instance(&winApi, &callback, CP_WINUNICODE)),
		std::exception);
}}

// ���������������� ��������������� ����������� ���������
TEST_F(InstanceTest, testConstruct_ConsistentCreationOk) {{
	InSequence s;
	EXPECT_INITIALIZE();
	EXPECT_UNINITIALIZE();
	EXPECT_INITIALIZE();
	EXPECT_UNINITIALIZE();

	Instance* instance1 = new Instance(&winApi, &callback, CP_WINANSI);
	instance1->drop();
	ASSERT_NO_THROW(auto_drop<Instance>
		instance2(new Instance(&winApi, &callback, CP_WINANSI)));
}}

// ���� ���������� ������������ ��������
TEST_F(InstanceTest, testAccessors) {{
	InSequence s;
	EXPECT_INITIALIZE();
	EXPECT_UNINITIALIZE();

	auto_drop<Instance> instance(new Instance(&winApi, &callback, CP_WINANSI));

	ASSERT_EQ(&winApi, instance->getWinApi());
	ASSERT_EQ(&callback, instance->getCallbackHandler());
}}

// ���� �������� ����� DDE-������
TEST_F(InstanceTest, testCreateString) {{
	HSZ hStr = (HSZ)77665;
	InSequence s;
	EXPECT_INITIALIZE();
	EXPECT_CALL(winApi, DdeCreateStringHandle(12345, StrEq("new str"),
			CP_WINUNICODE))
		.Times(1)
		.WillOnce(Return(hStr));
	EXPECT_CALL(winApi, DdeFreeStringHandle(12345, hStr));
	EXPECT_UNINITIALIZE();

	auto_drop<Instance> instance
		(new Instance(&winApi, &callback, CP_WINUNICODE));
	auto_drop<IString> str(instance->createString("new str"));

	ASSERT_NE((IString*)0, str.get());
	ASSERT_EQ(hStr, str->getHandle());
	ASSERT_EQ(CP_WINUNICODE, str->getCodePage());
}}

// ���� �������� ������ �� ������ ������������ DDE-������
TEST_F(InstanceTest, testWrapString_NotNullHandle) {{
	HSZ hStr = (HSZ)77621;
	InSequence s;
	EXPECT_INITIALIZE();
	EXPECT_UNINITIALIZE();
	auto_drop<Instance> instance(new Instance(&winApi, &callback, CP_WINANSI));
	auto_drop<IString> str(instance->wrapString(hStr));

	ASSERT_NE((IString*)0, str.get());
	ASSERT_EQ(hStr, str->getHandle());
	ASSERT_EQ(CP_WINANSI, str->getCodePage());
}}

// ���� �������� ������ �� ������ ������������, ���� ���������� ����� ����
TEST_F(InstanceTest, testWrapString_NullHandle) {{
	InSequence s;
	EXPECT_INITIALIZE();
	EXPECT_UNINITIALIZE();

	auto_drop<Instance> instance(new Instance(&winApi, &callback, CP_WINANSI));

	ASSERT_EQ(NULL, instance->wrapString(NULL));
}}

// ���� �������� ������� ������ �� ������ ������������ DDE-������
TEST_F(InstanceTest, testWrapData_NotNullHandle) {{
	HDDEDATA hData = (HDDEDATA)11442;
	
	InSequence s;
	EXPECT_INITIALIZE();
	EXPECT_UNINITIALIZE();

	auto_drop<Instance> instance(new Instance(&winApi, &callback, CP_WINANSI));
	auto_drop<IData> data(instance->wrapData(hData));

	ASSERT_NE((IData*)0, data.get());
	ASSERT_EQ(hData, data->getHandle());
}}

// ���� �������� ������� ������ �� ������ ������������ DDE-������,
// ���� ���������� ����� ����
TEST_F(InstanceTest, testWrapData_NullHandle) {{
	InSequence s;
	EXPECT_INITIALIZE();
	EXPECT_UNINITIALIZE();

	auto_drop<Instance> instance(new Instance(&winApi, &callback, CP_WINANSI));
	auto_drop<IData> data(instance->wrapData(NULL));

	ASSERT_EQ(NULL, data.get());
}}

// ���� �������� ������� ����������� ��� ��������� �����������
TEST_F(InstanceTest, testWrapConversation_NotNullHandle) {{
	HCONV hConv = (HCONV)11982;

	InSequence s;
	EXPECT_INITIALIZE();
	EXPECT_UNINITIALIZE();

	auto_drop<Instance> instance(new Instance(&winApi, &callback, CP_WINANSI));
	auto_drop<IConversation> conv(instance->wrapConversation(hConv));

	ASSERT_NE((IConversation*)0, conv.get());
	ASSERT_EQ(hConv, conv->getHandle());
}}

// ���� �������� ������� ����������� ��� ������� �����������
TEST_F(InstanceTest, testWrapConversation_NullHandle) {{
	InSequence s;
	EXPECT_INITIALIZE();
	EXPECT_UNINITIALIZE();

	auto_drop<Instance> instance(new Instance(&winApi, &callback, CP_WINANSI));
	auto_drop<IConversation> conv(instance->wrapConversation(NULL));

	ASSERT_EQ((IConversation*)0, conv.get());
}}

// ���� ��������� ���� ������
TEST_F(InstanceTest, testGetLastError) {{
	InSequence s;
	EXPECT_INITIALIZE();
	EXPECT_CALL(winApi, DdeGetLastError(12345))
		.Times(1)
		.WillOnce(Return(222));
	EXPECT_UNINITIALIZE();

	auto_drop<Instance> instance(new Instance(&winApi, &callback, CP_WINANSI));

	ASSERT_EQ(222, instance->getLastError());
}}

// ���� nameService
TEST_F(InstanceTest, testNameService) {{
	HSZ hStr = (HSZ)11223;
	
	InSequence s;
	EXPECT_INITIALIZE();
	EXPECT_CALL(winApi, DdeNameService(12345, hStr, 0, DNS_REGISTER))
		.Times(1)
		.WillOnce(Return((HDDEDATA)1));
	EXPECT_UNINITIALIZE();

	auto_drop<Instance> instance(new Instance(&winApi, &callback, CP_WINANSI));
	auto_drop<IString> str(instance->wrapString(hStr));
	instance->nameService(str, DNS_REGISTER);
}}

// ���� ��������� �������������� ��������
TEST_F(InstanceTest, testGetId) {{
	InSequence s;
	EXPECT_INITIALIZE();
	EXPECT_UNINITIALIZE();

	auto_drop<Instance> instance(new Instance(&winApi, &callback, CP_WINANSI));
	ASSERT_EQ(12345, instance->getId());
}}

// ���� ��������� ��������� �����
TEST_F(InstanceTest, testGetCodePage) {{
	InSequence s;
	EXPECT_INITIALIZE();
	EXPECT_UNINITIALIZE();

	auto_drop<Instance> instance
		(new Instance(&winApi, &callback, CP_WINUNICODE));
	ASSERT_EQ(CP_WINUNICODE, instance->getCodePage());
}}


/**
 * ============================================================================
 *
 * ������������ DDE ���������� 
 *
 * ============================================================================
 */

/**
 * ���������, ������������ ��������� ������ ������� ��������� ������
 * Instance::CallbackFunction � ��������� ��������� ����� ������.
 */ 
struct InstanceTest_DdeCallbackSpec {
	// ���������, ��������������� ���������� ������� ��������� ������.
	UINT uType;
	UINT uFmt;
	HCONV hConv;
	HSZ hsz1;
	HSZ hsz2;
	HDDEDATA hData;
	ULONG_PTR dwData1;
	ULONG_PTR dwData2;

	HDDEDATA expectedResult; // ��������� ��������� ������.
};

/**
 * ������� ����� ����� ��������� DDE-����������
 */
template <typename T>
class InstanceTest_TransactionTest :
	public TestWithParam<T>
{
protected:
	MockWinApi winApi;
	MockCallbackHandler callback;

	virtual InstanceTest_DdeCallbackSpec getCallbackSpec()=0;
	virtual void setHandlerExpectations()=0;
	virtual int getCodePage()=0;

	void testHandle() {{
		InSequence s;
		EXPECT_CALL(winApi, DdeInitialize(_, &Instance::CallbackFunction, 0, 0))
			.Times(1)
			.WillOnce(DoAll(
				SetArgumentPointee<0>(12345),
				Return(DMLERR_NO_ERROR)
			));
		auto_drop<Instance> instance
			(new Instance(&winApi, &callback, getCodePage()));
		setHandlerExpectations();
		EXPECT_CALL(winApi, DdeUninitialize(12345))
			.Times(1)
			.WillOnce(Return(TRUE));

		InstanceTest_DdeCallbackSpec cb = getCallbackSpec();
		HDDEDATA result = Instance::CallbackFunction(cb.uType, cb.uFmt,
			cb.hConv, cb.hsz1, cb.hsz2, cb.hData, cb.dwData1, cb.dwData2);
	
		ASSERT_EQ(result, cb.expectedResult);
	}}

};

/**
 * ============================================================================
 * ������������ ���������� XTYP_CONNECT
 * ============================================================================
 */

/**
 * ��������� � ��������� ������ ICallbackHandler::onConnect.
 */
struct InstanceTest_OnConnectSpec {
	int codePage; // ��������� ��������� �����
	HSZ hsz1; // ��������� ���������� ������ ������
	HSZ hsz2; // ��������� ���������� ������ ������
	PCONVCONTEXT pContext; // ��������� ��������� �� ��������� ���������
	bool isSameInstance; // ��������� ������� ���� �� ����������
	bool returnResult; // ��������� ���������

	InstanceTest_DdeCallbackSpec cb; // ��������� ������� ��������� ������ 
};


/**
 * ��������� ������ ��� �������������������� ����� XTYP_CONNECT
 */
::std::vector<InstanceTest_OnConnectSpec>
	InstanceTest_XTYP_CONNECT_Params()
{
	::std::vector<InstanceTest_OnConnectSpec> v;
	InstanceTest_OnConnectSpec spec;

	// ������� ����� � TRUE �����������
	memset(&spec, 0, sizeof(spec));
	spec.cb.uType = XTYP_CONNECT;
	spec.codePage = CP_WINANSI;
	spec.hsz1 = spec.cb.hsz1 = (HSZ)112345;
	spec.hsz2 = spec.cb.hsz2 = (HSZ)889213;
	spec.pContext = (PCONVCONTEXT)887721; spec.cb.dwData1 = 887721;
	spec.isSameInstance = false; spec.cb.dwData2 = 0;
	spec.returnResult = true; spec.cb.expectedResult = (HDDEDATA)TRUE;
	v.push_back(spec);


	// ������� ����� � FALSE ����������� (������ �� ����������)
	spec.returnResult = false; spec.cb.expectedResult = (HDDEDATA)FALSE;
	v.push_back(spec);

	// ����� � ������� ����������
	spec.pContext = NULL; spec.cb.dwData1 = 0;
	v.push_back(spec);

	// ����� �� ���� �� ���������� ��������.
	spec.isSameInstance = true; spec.cb.dwData2 = 1;
	v.push_back(spec);

	return v;
}

/**
 * ���� ���������� XTYP_CONNECT
 */
class InstanceTest_XTYP_CONNECT :
	public InstanceTest_TransactionTest<InstanceTest_OnConnectSpec>
{
protected:
	
	InstanceTest_DdeCallbackSpec getCallbackSpec() {
		return GetParam().cb;
	}

	void setHandlerExpectations() {
		EXPECT_CALL(callback, onConnect(
				IsString(GetParam().hsz1, GetParam().codePage),
				IsString(GetParam().hsz2, GetParam().codePage),
				GetParam().pContext, GetParam().isSameInstance))
			.Times(1)
			.WillOnce(Return(GetParam().returnResult));
	}

	int getCodePage() {
		return GetParam().codePage;
	}

};

TEST_P(InstanceTest_XTYP_CONNECT, testHandle) {
	InstanceTest_TransactionTest::testHandle();
}

INSTANTIATE_TEST_CASE_P(InstanceTest,
	InstanceTest_XTYP_CONNECT,
	ValuesIn(InstanceTest_XTYP_CONNECT_Params()));



/**
 * ============================================================================
 * ������������ ���������� XTYP_CONNECT_CONFIRM
 * ============================================================================
 */

/**
 * ��������� � ��������� ������ ICallbackHandler::onConnectConfirm.
 */
struct InstanceTest_OnConnectConfirmSpec {
	int codePage; // ��������� ��������� �����
	HCONV hConv; // ��������� ���������� �����������
	HSZ hsz1; // ��������� ���������� ������ ������
	HSZ hsz2; // ��������� ���������� ������ ������
	bool isSameInstance; // ��������� ������� ���� �� ����������

	InstanceTest_DdeCallbackSpec cb; // ��������� ������� ��������� ������ 
};

/**
 * ��������� ������ ��� �������������������� ����� XTYP_CONNECT_CONFIRM
 */
::std::vector<InstanceTest_OnConnectConfirmSpec>
	InstanceTest_XTYP_CONNECT_CONFIRM_Params()
{
	::std::vector<InstanceTest_OnConnectConfirmSpec> v;
	InstanceTest_OnConnectConfirmSpec spec;

	// ������� �����
	memset(&spec, 0, sizeof(spec));
	spec.cb.uType = XTYP_CONNECT_CONFIRM;
	spec.codePage = CP_WINANSI;
	spec.hsz1 = spec.cb.hsz1 = (HSZ)887212;
	spec.hsz2 = spec.cb.hsz2 = (HSZ)112233;
	spec.hConv = spec.cb.hConv = (HCONV)998821;
	spec.isSameInstance = false; spec.cb.dwData2 = 0;
	spec.cb.expectedResult = (HDDEDATA)0;
	v.push_back(spec);

	// ������� ����� (��� �� ��������� DDE ��������)
	spec.isSameInstance = true; spec.cb.dwData2 = 1;
	v.push_back(spec);

	return v;
}

/**
 * ���� ���������� XTYP_CONNECT_CONFIRM
 */
class InstanceTest_XTYP_CONNECT_CONFIRM :
	public InstanceTest_TransactionTest<InstanceTest_OnConnectConfirmSpec>
{
protected:
	
	InstanceTest_DdeCallbackSpec getCallbackSpec() {
		return GetParam().cb;
	}

	void setHandlerExpectations() {
		EXPECT_CALL(callback, onConnectConfirm(
				IsConversation(GetParam().hConv),
				IsString(GetParam().hsz1, GetParam().codePage),
				IsString(GetParam().hsz2, GetParam().codePage),
				GetParam().isSameInstance))
			.Times(1);
	}

	int getCodePage() {
		return GetParam().codePage;
	}

};

TEST_P(InstanceTest_XTYP_CONNECT_CONFIRM, testHandle) {
	InstanceTest_TransactionTest::testHandle();
}

INSTANTIATE_TEST_CASE_P(InstanceTest,
	InstanceTest_XTYP_CONNECT_CONFIRM,
	ValuesIn(InstanceTest_XTYP_CONNECT_CONFIRM_Params()));



/**
 * ============================================================================
 * ������������ ���������� XTYP_DISCONNECT
 * ============================================================================
 */

/**
 * ��������� � ��������� ������ ICallbackHandler::onDisconnect.
 */
struct InstanceTest_OnDisconnectSpec {
	HCONV hConv; // ��������� ���������� �����������
	bool isSameInstance; // ��������� ������� ���� �� ����������

	InstanceTest_DdeCallbackSpec cb; // ��������� ������� ��������� ������ 
};

/**
 * ��������� ������ ��� �������������������� ����� XTYP_DISCONNECT
 */
::std::vector<InstanceTest_OnDisconnectSpec>
	InstanceTest_XTYP_DISCONNECT_Params()
{
	::std::vector<InstanceTest_OnDisconnectSpec> v;
	InstanceTest_OnDisconnectSpec spec;

	// ������� �����
	memset(&spec, 0, sizeof(spec));
	spec.cb.uType = XTYP_DISCONNECT;
	spec.hConv = spec.cb.hConv = (HCONV)999882;
	spec.isSameInstance = false; spec.cb.dwData2 = 0;
	spec.cb.expectedResult = (HDDEDATA)0;
	v.push_back(spec);

	// ������� ����� (��� �� ��������� DDE ��������)
	spec.isSameInstance = true; spec.cb.dwData2 = 1;
	v.push_back(spec);

	return v;
}

/**
 * ���� ���������� XTYP_DISCONNECT
 */
class InstanceTest_XTYP_DISCONNECT :
	public InstanceTest_TransactionTest<InstanceTest_OnDisconnectSpec>
{
protected:
	
	InstanceTest_DdeCallbackSpec getCallbackSpec() {
		return GetParam().cb;
	}

	void setHandlerExpectations() {
		EXPECT_CALL(callback, onDisconnect(
				IsConversation(GetParam().hConv),
				GetParam().isSameInstance))
			.Times(1);
	}

	int getCodePage() {
		return CP_WINANSI; // not used here
	}

};

TEST_P(InstanceTest_XTYP_DISCONNECT, testHandle) {
	InstanceTest_TransactionTest::testHandle();
}

INSTANTIATE_TEST_CASE_P(InstanceTest,
	InstanceTest_XTYP_DISCONNECT,
	ValuesIn(InstanceTest_XTYP_DISCONNECT_Params()));


/**
 * ============================================================================
 * ������������ ���������� XTYP_POKE
 * ============================================================================
 */

/**
 * ��������� � ��������� ������ ICallbackHandler::onPoke.
 */
struct InstanceTest_OnPokeSpec {
	UINT uFmt; // ��������� ������ ������
	HCONV hConv; // ��������� ���������� �����������
	HSZ hsz1; // ��������� ���������� ������ ������
	HSZ hsz2; // ��������� ���������� ������ ������
	HDDEDATA hData; // ��������� ���������� ������
	bool isSameInstance; // ��������� ������� ���� �� ����������

	int returnResult; // ������������ ���������

	InstanceTest_DdeCallbackSpec cb; // ��������� ������� ��������� ������ 
};

/**
 * ��������� ������ ��� �������������������� ����� XTYP_POKE
 */
::std::vector<InstanceTest_OnPokeSpec>
	InstanceTest_XTYP_POKE_Params()
{
	::std::vector<InstanceTest_OnPokeSpec> v;
	InstanceTest_OnPokeSpec spec;

	// ������� ����� � ��������� DDE_FACK
	memset(&spec, 0, sizeof(spec));
	spec.cb.uType = XTYP_POKE;
	spec.cb.uFmt = spec.uFmt = 1122;
	spec.hConv = spec.cb.hConv = (HCONV)999882;
	spec.hsz1 = spec.cb.hsz1 = (HSZ)776655;
	spec.hsz2 = spec.cb.hsz2 = (HSZ)443322;
	spec.hData = spec.cb.hData = (HDDEDATA)992121;
	spec.cb.expectedResult = (HDDEDATA)DDE_FACK;
	spec.returnResult = DDE_FACK;
	v.push_back(spec);

	// ������� ����� � ��������� DDE_FBUSY
	spec.cb.expectedResult = (HDDEDATA)DDE_FBUSY;
	spec.returnResult = DDE_FBUSY;
	v.push_back(spec);

	// ������� ����� � ��������� DDE_FNOTPROCESSED
	spec.cb.expectedResult = (HDDEDATA)DDE_FNOTPROCESSED;
	spec.returnResult = DDE_FNOTPROCESSED;
	v.push_back(spec);

	return v;
}

/**
 * ���� ���������� XTYP_POKE
 */
class InstanceTest_XTYP_POKE :
	public InstanceTest_TransactionTest<InstanceTest_OnPokeSpec>
{
protected:
	
	InstanceTest_DdeCallbackSpec getCallbackSpec() {
		return GetParam().cb;
	}

	void setHandlerExpectations() {
		EXPECT_CALL(callback, onPoke(GetParam().uFmt,
				IsConversation(GetParam().hConv),
				IsString(GetParam().hsz1, getCodePage()),
				IsString(GetParam().hsz2, getCodePage()),
				IsData(GetParam().hData)))
			.Times(1)
			.WillOnce(Return(GetParam().returnResult));
	}

	int getCodePage() {
		return CP_WINANSI; // not used here
	}

};

TEST_P(InstanceTest_XTYP_POKE, testHandle) {
	InstanceTest_TransactionTest::testHandle();
}

INSTANTIATE_TEST_CASE_P(InstanceTest,
	InstanceTest_XTYP_POKE,
	ValuesIn(InstanceTest_XTYP_POKE_Params()));


/**
 * ============================================================================
 * ������������ ���������� XTYP_REGISTER
 * ============================================================================
 */

/**
 * ��������� � ��������� ������ ICallbackHandler::onRegister.
 */
struct InstanceTest_OnRegisterSpec {
	HSZ hsz1; // ��������� ���������� ������ ������
	HSZ hsz2; // ��������� ���������� ������ ������

	InstanceTest_DdeCallbackSpec cb; // ��������� ������� ��������� ������ 
};

/**
 * ��������� ������ ��� �������������������� ����� XTYP_REGISTER
 */
::std::vector<InstanceTest_OnRegisterSpec>
	InstanceTest_XTYP_REGISTER_Params()
{
	::std::vector<InstanceTest_OnRegisterSpec> v;
	InstanceTest_OnRegisterSpec spec;

	// ������� �����
	memset(&spec, 0, sizeof(spec));
	spec.cb.uType = XTYP_REGISTER;
	spec.hsz1 = spec.cb.hsz1 = (HSZ)112233;
	spec.hsz2 = spec.cb.hsz2 = (HSZ)332211;
	spec.cb.expectedResult = (HDDEDATA)0;
	v.push_back(spec);

	return v;
}

/**
 * ���� ���������� XTYP_REGISTER
 */
class InstanceTest_XTYP_REGISTER :
	public InstanceTest_TransactionTest<InstanceTest_OnRegisterSpec>
{
protected:
	
	InstanceTest_DdeCallbackSpec getCallbackSpec() {
		return GetParam().cb;
	}

	void setHandlerExpectations() {
		EXPECT_CALL(callback, onRegister(
				IsString(GetParam().hsz1, getCodePage()),
				IsString(GetParam().hsz2, getCodePage())))
			.Times(1);
	}

	int getCodePage() {
		return CP_WINUNICODE; // not used here
	}

};

TEST_P(InstanceTest_XTYP_REGISTER, testHandle) {
	InstanceTest_TransactionTest::testHandle();
}

INSTANTIATE_TEST_CASE_P(InstanceTest,
	InstanceTest_XTYP_REGISTER,
	ValuesIn(InstanceTest_XTYP_REGISTER_Params()));



/**
 * ============================================================================
 * ������������ ���������� XTYP_UNREGISTER
 * ============================================================================
 */

/**
 * ��������� � ��������� ������ ICallbackHandler::onUnregister.
 */
struct InstanceTest_OnUnregisterSpec {
	HSZ hsz1; // ��������� ���������� ������ ������
	HSZ hsz2; // ��������� ���������� ������ ������

	InstanceTest_DdeCallbackSpec cb; // ��������� ������� ��������� ������ 
};

/**
 * ��������� ������ ��� �������������������� ����� XTYP_UNREGISTER
 */
::std::vector<InstanceTest_OnUnregisterSpec>
	InstanceTest_XTYP_UNREGISTER_Params()
{
	::std::vector<InstanceTest_OnUnregisterSpec> v;
	InstanceTest_OnUnregisterSpec spec;

	// ������� �����
	memset(&spec, 0, sizeof(spec));
	spec.cb.uType = XTYP_UNREGISTER;
	spec.hsz1 = spec.cb.hsz1 = (HSZ)112233;
	spec.hsz2 = spec.cb.hsz2 = (HSZ)332211;
	spec.cb.expectedResult = (HDDEDATA)0;
	v.push_back(spec);

	return v;
}

/**
 * ���� ���������� XTYP_UNREGISTER
 */
class InstanceTest_XTYP_UNREGISTER :
	public InstanceTest_TransactionTest<InstanceTest_OnUnregisterSpec>
{
protected:
	
	InstanceTest_DdeCallbackSpec getCallbackSpec() {
		return GetParam().cb;
	}

	void setHandlerExpectations() {
		EXPECT_CALL(callback, onUnregister(
				IsString(GetParam().hsz1, getCodePage()),
				IsString(GetParam().hsz2, getCodePage())))
			.Times(1);
	}

	int getCodePage() {
		return CP_WINUNICODE; // not used here
	}

};

TEST_P(InstanceTest_XTYP_UNREGISTER, testHandle) {
	InstanceTest_TransactionTest::testHandle();
}

INSTANTIATE_TEST_CASE_P(InstanceTest,
	InstanceTest_XTYP_UNREGISTER,
	ValuesIn(InstanceTest_XTYP_UNREGISTER_Params()));


	} // end namespace dde
} // end namespace aquila