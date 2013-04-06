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


	// Установить ожидание вызова инициализации DDE инстанса
	void EXPECT_INITIALIZE() {
		EXPECT_CALL(winApi, DdeInitialize(_, &Instance::CallbackFunction, 0, 0))
			.Times(1)
			.WillOnce(DoAll(
				SetArgumentPointee<0>(12345),
				Return(DMLERR_NO_ERROR)
			));
	}

	// Установить ожидание вызова деинициализации инстанса DDE
	void EXPECT_UNINITIALIZE() {
		EXPECT_CALL(winApi, DdeUninitialize(12345))
			.Times(1)
			.WillOnce(Return(TRUE));
	}

protected:
	MockWinApi winApi;
	MockCallbackHandler callback;
};


// Тест конструктора
TEST_F(InstanceTest, testConstruct_Ok) {{
	InSequence s;
	EXPECT_INITIALIZE();
	EXPECT_UNINITIALIZE();

	auto_drop<Instance> instance(new Instance(&winApi, &callback, CP_WINANSI));

	ASSERT_EQ(2, winApi.getRefCount());
	ASSERT_EQ(2, callback.getRefCount());
	ASSERT_EQ(1, instance->getRefCount());
}}

// Конструктор выбрасывает исключение, если неудалось инициализировать DDE
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

// Конструктор выбрасывает исключение при попытке инстанцировать
// более одного экземпляра
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

// Последовательное инстанцирование экземпляров разрешено
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

// Тест акцессоров используемых объектов
TEST_F(InstanceTest, testAccessors) {{
	InSequence s;
	EXPECT_INITIALIZE();
	EXPECT_UNINITIALIZE();

	auto_drop<Instance> instance(new Instance(&winApi, &callback, CP_WINANSI));

	ASSERT_EQ(&winApi, instance->getWinApi());
	ASSERT_EQ(&callback, instance->getCallbackHandler());
}}

// Тест создания новой DDE-строки
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

// Тест создания строки на основе существующей DDE-строки
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

// Тест создания строки на основе существующей, если дескриптор равен нулю
TEST_F(InstanceTest, testWrapString_NullHandle) {{
	InSequence s;
	EXPECT_INITIALIZE();
	EXPECT_UNINITIALIZE();

	auto_drop<Instance> instance(new Instance(&winApi, &callback, CP_WINANSI));

	ASSERT_EQ(NULL, instance->wrapString(NULL));
}}

// Тест создания объекта данных на основе существующих DDE-данных
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

// Тест создания объекта данных на основе существующих DDE-данных,
// если дескриптор равен нулю
TEST_F(InstanceTest, testWrapData_NullHandle) {{
	InSequence s;
	EXPECT_INITIALIZE();
	EXPECT_UNINITIALIZE();

	auto_drop<Instance> instance(new Instance(&winApi, &callback, CP_WINANSI));
	auto_drop<IData> data(instance->wrapData(NULL));

	ASSERT_EQ(NULL, data.get());
}}

// Тест создания объекта подключения при ненулевом дескрипторе
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

// Тест создания объекта подключения при нулевом дескрипторе
TEST_F(InstanceTest, testWrapConversation_NullHandle) {{
	InSequence s;
	EXPECT_INITIALIZE();
	EXPECT_UNINITIALIZE();

	auto_drop<Instance> instance(new Instance(&winApi, &callback, CP_WINANSI));
	auto_drop<IConversation> conv(instance->wrapConversation(NULL));

	ASSERT_EQ((IConversation*)0, conv.get());
}}

// Тест получения кода ошибки
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

// Тест nameService
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

// Тест получения идентификатора инстанса
TEST_F(InstanceTest, testGetId) {{
	InSequence s;
	EXPECT_INITIALIZE();
	EXPECT_UNINITIALIZE();

	auto_drop<Instance> instance(new Instance(&winApi, &callback, CP_WINANSI));
	ASSERT_EQ(12345, instance->getId());
}}

// Тест получения кодировки строк
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
 * Тестирование DDE транзакции 
 *
 * ============================================================================
 */

/**
 * Структура, определяющая параметры вызова функции обратного вызова
 * Instance::CallbackFunction и ожидаемый результат этого вызова.
 */ 
struct InstanceTest_DdeCallbackSpec {
	// Параметры, соответствующие аргументам функции обратного вызова.
	UINT uType;
	UINT uFmt;
	HCONV hConv;
	HSZ hsz1;
	HSZ hsz2;
	HDDEDATA hData;
	ULONG_PTR dwData1;
	ULONG_PTR dwData2;

	HDDEDATA expectedResult; // Ожидаемый результат вызова.
};

/**
 * Базовый класс теста обработки DDE-транзакции
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
 * Тестирование транзакции XTYP_CONNECT
 * ============================================================================
 */

/**
 * Параметры и результат вызова ICallbackHandler::onConnect.
 */
struct InstanceTest_OnConnectSpec {
	int codePage; // ожидаемая кодировка строк
	HSZ hsz1; // ожидаемый дескриптор первой строки
	HSZ hsz2; // ожидаемый дескриптор второй строки
	PCONVCONTEXT pContext; // ожидаемый указатель на структуру контекста
	bool isSameInstance; // ожидаемый признак того же экземпляра
	bool returnResult; // ожидаемый результат

	InstanceTest_DdeCallbackSpec cb; // параметры функции обратного вызова 
};


/**
 * Генератор данных для параметризированного теста XTYP_CONNECT
 */
::std::vector<InstanceTest_OnConnectSpec>
	InstanceTest_XTYP_CONNECT_Params()
{
	::std::vector<InstanceTest_OnConnectSpec> v;
	InstanceTest_OnConnectSpec spec;

	// Обычный вызов с TRUE результатом
	memset(&spec, 0, sizeof(spec));
	spec.cb.uType = XTYP_CONNECT;
	spec.codePage = CP_WINANSI;
	spec.hsz1 = spec.cb.hsz1 = (HSZ)112345;
	spec.hsz2 = spec.cb.hsz2 = (HSZ)889213;
	spec.pContext = (PCONVCONTEXT)887721; spec.cb.dwData1 = 887721;
	spec.isSameInstance = false; spec.cb.dwData2 = 0;
	spec.returnResult = true; spec.cb.expectedResult = (HDDEDATA)TRUE;
	v.push_back(spec);


	// Обычный вызов с FALSE результатом (запрет на соединение)
	spec.returnResult = false; spec.cb.expectedResult = (HDDEDATA)FALSE;
	v.push_back(spec);

	// Вызов с нулевым контекстом
	spec.pContext = NULL; spec.cb.dwData1 = 0;
	v.push_back(spec);

	// Вызов из того же экземпляра инстанса.
	spec.isSameInstance = true; spec.cb.dwData2 = 1;
	v.push_back(spec);

	return v;
}

/**
 * Тест транзакции XTYP_CONNECT
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
 * Тестирование транзакции XTYP_CONNECT_CONFIRM
 * ============================================================================
 */

/**
 * Параметры и результат вызова ICallbackHandler::onConnectConfirm.
 */
struct InstanceTest_OnConnectConfirmSpec {
	int codePage; // ожидаемая кодировка строк
	HCONV hConv; // ожидаемый дескриптор подключения
	HSZ hsz1; // ожидаемый дескриптор первой строки
	HSZ hsz2; // ожидаемый дескриптор второй строки
	bool isSameInstance; // ожидаемый признак того же экземпляра

	InstanceTest_DdeCallbackSpec cb; // параметры функции обратного вызова 
};

/**
 * Генератор данных для параметризированного теста XTYP_CONNECT_CONFIRM
 */
::std::vector<InstanceTest_OnConnectConfirmSpec>
	InstanceTest_XTYP_CONNECT_CONFIRM_Params()
{
	::std::vector<InstanceTest_OnConnectConfirmSpec> v;
	InstanceTest_OnConnectConfirmSpec spec;

	// Обычный вызов
	memset(&spec, 0, sizeof(spec));
	spec.cb.uType = XTYP_CONNECT_CONFIRM;
	spec.codePage = CP_WINANSI;
	spec.hsz1 = spec.cb.hsz1 = (HSZ)887212;
	spec.hsz2 = spec.cb.hsz2 = (HSZ)112233;
	spec.hConv = spec.cb.hConv = (HCONV)998821;
	spec.isSameInstance = false; spec.cb.dwData2 = 0;
	spec.cb.expectedResult = (HDDEDATA)0;
	v.push_back(spec);

	// Обычный вызов (тот же экземпляр DDE инстанса)
	spec.isSameInstance = true; spec.cb.dwData2 = 1;
	v.push_back(spec);

	return v;
}

/**
 * Тест транзакции XTYP_CONNECT_CONFIRM
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
 * Тестирование транзакции XTYP_DISCONNECT
 * ============================================================================
 */

/**
 * Параметры и результат вызова ICallbackHandler::onDisconnect.
 */
struct InstanceTest_OnDisconnectSpec {
	HCONV hConv; // ожидаемый дескриптор подключения
	bool isSameInstance; // ожидаемый признак того же экземпляра

	InstanceTest_DdeCallbackSpec cb; // параметры функции обратного вызова 
};

/**
 * Генератор данных для параметризированного теста XTYP_DISCONNECT
 */
::std::vector<InstanceTest_OnDisconnectSpec>
	InstanceTest_XTYP_DISCONNECT_Params()
{
	::std::vector<InstanceTest_OnDisconnectSpec> v;
	InstanceTest_OnDisconnectSpec spec;

	// Обычный вызов
	memset(&spec, 0, sizeof(spec));
	spec.cb.uType = XTYP_DISCONNECT;
	spec.hConv = spec.cb.hConv = (HCONV)999882;
	spec.isSameInstance = false; spec.cb.dwData2 = 0;
	spec.cb.expectedResult = (HDDEDATA)0;
	v.push_back(spec);

	// Обычный вызов (тот же экземпляр DDE инстанса)
	spec.isSameInstance = true; spec.cb.dwData2 = 1;
	v.push_back(spec);

	return v;
}

/**
 * Тест транзакции XTYP_DISCONNECT
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
 * Тестирование транзакции XTYP_POKE
 * ============================================================================
 */

/**
 * Параметры и результат вызова ICallbackHandler::onPoke.
 */
struct InstanceTest_OnPokeSpec {
	UINT uFmt; // ожидаемый формат данных
	HCONV hConv; // ожидаемый дескриптор подключения
	HSZ hsz1; // ожидаемый дескриптор первой строки
	HSZ hsz2; // ожидаемый дескриптор второй строки
	HDDEDATA hData; // ожидаемый дескриптор данных
	bool isSameInstance; // ожидаемый признак того же экземпляра

	int returnResult; // возвращаемый результат

	InstanceTest_DdeCallbackSpec cb; // параметры функции обратного вызова 
};

/**
 * Генератор данных для параметризированного теста XTYP_POKE
 */
::std::vector<InstanceTest_OnPokeSpec>
	InstanceTest_XTYP_POKE_Params()
{
	::std::vector<InstanceTest_OnPokeSpec> v;
	InstanceTest_OnPokeSpec spec;

	// Обычный вызов с возвратом DDE_FACK
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

	// Обычный вызов с возвратом DDE_FBUSY
	spec.cb.expectedResult = (HDDEDATA)DDE_FBUSY;
	spec.returnResult = DDE_FBUSY;
	v.push_back(spec);

	// Обычный вызов с возвратом DDE_FNOTPROCESSED
	spec.cb.expectedResult = (HDDEDATA)DDE_FNOTPROCESSED;
	spec.returnResult = DDE_FNOTPROCESSED;
	v.push_back(spec);

	return v;
}

/**
 * Тест транзакции XTYP_POKE
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
 * Тестирование транзакции XTYP_REGISTER
 * ============================================================================
 */

/**
 * Параметры и результат вызова ICallbackHandler::onRegister.
 */
struct InstanceTest_OnRegisterSpec {
	HSZ hsz1; // ожидаемый дескриптор первой строки
	HSZ hsz2; // ожидаемый дескриптор второй строки

	InstanceTest_DdeCallbackSpec cb; // параметры функции обратного вызова 
};

/**
 * Генератор данных для параметризированного теста XTYP_REGISTER
 */
::std::vector<InstanceTest_OnRegisterSpec>
	InstanceTest_XTYP_REGISTER_Params()
{
	::std::vector<InstanceTest_OnRegisterSpec> v;
	InstanceTest_OnRegisterSpec spec;

	// Обычный вызов
	memset(&spec, 0, sizeof(spec));
	spec.cb.uType = XTYP_REGISTER;
	spec.hsz1 = spec.cb.hsz1 = (HSZ)112233;
	spec.hsz2 = spec.cb.hsz2 = (HSZ)332211;
	spec.cb.expectedResult = (HDDEDATA)0;
	v.push_back(spec);

	return v;
}

/**
 * Тест транзакции XTYP_REGISTER
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
 * Тестирование транзакции XTYP_UNREGISTER
 * ============================================================================
 */

/**
 * Параметры и результат вызова ICallbackHandler::onUnregister.
 */
struct InstanceTest_OnUnregisterSpec {
	HSZ hsz1; // ожидаемый дескриптор первой строки
	HSZ hsz2; // ожидаемый дескриптор второй строки

	InstanceTest_DdeCallbackSpec cb; // параметры функции обратного вызова 
};

/**
 * Генератор данных для параметризированного теста XTYP_UNREGISTER
 */
::std::vector<InstanceTest_OnUnregisterSpec>
	InstanceTest_XTYP_UNREGISTER_Params()
{
	::std::vector<InstanceTest_OnUnregisterSpec> v;
	InstanceTest_OnUnregisterSpec spec;

	// Обычный вызов
	memset(&spec, 0, sizeof(spec));
	spec.cb.uType = XTYP_UNREGISTER;
	spec.hsz1 = spec.cb.hsz1 = (HSZ)112233;
	spec.hsz2 = spec.cb.hsz2 = (HSZ)332211;
	spec.cb.expectedResult = (HDDEDATA)0;
	v.push_back(spec);

	return v;
}

/**
 * Тест транзакции XTYP_UNREGISTER
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