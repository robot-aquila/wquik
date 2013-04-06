/**
 * ============================================================================
 * 2011/08/03
 * $Id: ServerTest.cpp 235 2012-07-23 15:52:48Z whirlwind $
 * ============================================================================
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/dde/macros.h"
#include "aquila/dde/MockCallbackHandler.h"
#include "aquila/core/auto_drop.h"
#include "aquila/core/WinApi.h"
#include "aquila/ddesvr/MockServiceMap.h"
#include "aquila/ddesvr/MockHelperWindowThread.h"
#include "aquila/ddesvr/MockHelperWindowController.h"
#include "aquila/core/MockThread.h"
#include "aquila/core/MockEvent.h"
#include "aquila/core/MockMutex.h"
#include "aquila/core/MockCriticalSection.h"
#include "aquila/core/MockWinApi.h"
#include "aquila/ddesvr/Server.h"

using namespace testing;

namespace aquila {
	namespace ddesvr {

class ServerTest : public ::testing::Test {
public:
	void SetUp() {
		WinApi::setInstance(&winApi);
	}

	void TearDown() {
		WinApi::setInstance(NULL);
	}

	void EXPECT_CONSTRUCTOR_CALLS() {
		// мьютекс не юзается, иначе дедлок при вызове фабричного
	}

	void EXPECT_DESTRUCTOR_CALLS() {
		EXPECT_CALL(winApi, createMutex(SERVER_MUTEX))
			.Times(1)
			.WillOnce(Return(&mutex));
		mutex.grab();
		EXPECT_CALL(cs, enter()).Times(1);
		EXPECT_CALL(cs, leave()).Times(1);
	}

protected:
	MockWinApi winApi;
	MockServiceMap sm;
	MockHelperWindowThread windowThread;
	MockCriticalSection cs;
	MockEvent e;
	MockThread thread;
	MockMutex mutex;
	MockHelperWindowController controller;
	MockCallbackHandler handler;
};

TEST_F(ServerTest, testConstructor_IncrementsRefCount) {{
	InSequence s;
	EXPECT_CONSTRUCTOR_CALLS();
	EXPECT_DESTRUCTOR_CALLS();

	auto_drop<Server> svr(new Server(&winApi, &sm, &windowThread, &cs, &e));
	ASSERT_EQ(2, winApi.getRefCount());
	ASSERT_EQ(2, sm.getRefCount());
	ASSERT_EQ(2, windowThread.getRefCount());
	ASSERT_EQ(2, cs.getRefCount());
	ASSERT_EQ(2, e.getRefCount());
}}

TEST_F(ServerTest, testDestructor_DecrementsRefCount) {{
	InSequence s;
	EXPECT_CONSTRUCTOR_CALLS();
	EXPECT_DESTRUCTOR_CALLS();

	Server* svr = new Server(&winApi, &sm, &windowThread, &cs, &e);
	delete svr;
	ASSERT_EQ(1, winApi.getRefCount());
	ASSERT_EQ(1, sm.getRefCount());
	ASSERT_EQ(1, windowThread.getRefCount());
	ASSERT_EQ(1, cs.getRefCount());
	ASSERT_EQ(1, e.getRefCount());
	ASSERT_EQ(1, mutex.getRefCount());
}}

TEST_F(ServerTest, testDestructor_FreesAllResourcesIfNotNull) {{
	InSequence s;
	EXPECT_CONSTRUCTOR_CALLS();
	EXPECT_DESTRUCTOR_CALLS();

	thread.grab();

	Server* svr = new Server(&winApi, &sm, &windowThread, &cs, &e);
	svr->test_setThread(&thread);
	delete svr;

	ASSERT_EQ(1, thread.getRefCount());
}}

TEST_F(ServerTest, testAccessors_Ok) {{
	InSequence s;
	EXPECT_CONSTRUCTOR_CALLS();
	EXPECT_DESTRUCTOR_CALLS();

	auto_drop<Server> svr(new Server(&winApi, &sm, &windowThread, &cs, &e));

	ASSERT_EQ(&winApi, svr->getWinApi());
	ASSERT_EQ(&sm, svr->getServiceMap());
	ASSERT_EQ(&windowThread, svr->getHelperWindowThread());
	ASSERT_EQ(&cs, svr->getCriticalSection());
	ASSERT_EQ(&e, svr->getEvent());
}}

TEST_F(ServerTest, testGetThread_IfNotStarted) {{
	InSequence s;
	EXPECT_CONSTRUCTOR_CALLS();
	EXPECT_CALL(cs, enter()).Times(1);
	EXPECT_CALL(cs, leave()).Times(1);
	EXPECT_DESTRUCTOR_CALLS();

	auto_drop<Server> svr(new Server(&winApi, &sm, &windowThread, &cs, &e));

	ASSERT_EQ((IThread*)NULL, svr->getThread());
}}

TEST_F(ServerTest, testGetThread_IfStarted) {{
	InSequence s;
	EXPECT_CONSTRUCTOR_CALLS();
	EXPECT_CALL(cs, enter()).Times(1);
	EXPECT_CALL(cs, leave()).Times(1);
	EXPECT_DESTRUCTOR_CALLS();

	auto_drop<Server> svr(new Server(&winApi, &sm, &windowThread, &cs, &e));
	svr->test_setThread(&thread);

	ASSERT_EQ(&thread, svr->getThread());

	svr->test_setThread(NULL);
}}

TEST_F(ServerTest, testStart_ThrowsIfAlreadyStarted) {{
	InSequence s;
	EXPECT_CONSTRUCTOR_CALLS();
	EXPECT_CALL(cs, enter()).Times(1);
	EXPECT_CALL(cs, leave()).Times(1);
	EXPECT_DESTRUCTOR_CALLS();

	auto_drop<Server> svr(new Server(&winApi, &sm, &windowThread, &cs, &e));
	svr->test_setThread(&thread);

	ASSERT_THROW(svr->start(), exception);

	svr->test_setThread(NULL);
}}

TEST_F(ServerTest, testStart_ThrowsIfThreadFinished) {{
	InSequence s;
	EXPECT_CONSTRUCTOR_CALLS();

	auto_drop<Server> svr(new Server(&winApi, &sm, &windowThread, &cs, &e));

	EXPECT_CALL(cs, enter()).Times(1);
	EXPECT_CALL(winApi, createThread(&windowThread)).Times(1)
		.WillOnce(Return(&thread));
	EXPECT_CALL(thread, start()).Times(1);
	EXPECT_CALL(e, getHandle()).Times(1)
		.WillOnce(Return((HANDLE)12345));
	EXPECT_CALL(thread, getHandle()).Times(1)
		.WillOnce(Return((HANDLE)54321));
	EXPECT_CALL(cs, leave()).Times(1);

	const HANDLE handles[] = { (HANDLE)12345, (HANDLE)54321 };
	EXPECT_CALL(winApi, WaitForMultipleObjects(2,
			IsBinaryEq(handles, sizeof(handles)), FALSE, INFINITE))
		.Times(1)
		.WillOnce(Return(WAIT_OBJECT_0 + 1)); // Thread signalled
	EXPECT_CALL(cs, enter()).Times(1);
	EXPECT_CALL(cs, leave()).Times(1);
	EXPECT_DESTRUCTOR_CALLS();

	thread.grab(); // дропнет сразу в clean up-е
	ASSERT_THROW(svr->start(), exception);
	ASSERT_EQ(1, thread.getRefCount());
}}

TEST_F(ServerTest, testStart_Ok) {{
	InSequence s;
	EXPECT_CONSTRUCTOR_CALLS();

	auto_drop<Server> svr(new Server(&winApi, &sm, &windowThread, &cs, &e));

	EXPECT_CALL(cs, enter()).Times(1);
	EXPECT_CALL(winApi, createThread(&windowThread)).Times(1)
		.WillOnce(Return(&thread));
	EXPECT_CALL(thread, start()).Times(1);
	EXPECT_CALL(e, getHandle()).Times(1)
		.WillOnce(Return((HANDLE)12345));
	EXPECT_CALL(thread, getHandle()).Times(1)
		.WillOnce(Return((HANDLE)54321));
	EXPECT_CALL(cs, leave()).Times(1);
	const HANDLE handles[] = { (HANDLE)12345, (HANDLE)54321 };
	EXPECT_CALL(winApi, WaitForMultipleObjects(2,
			IsBinaryEq(handles, sizeof(handles)), FALSE, INFINITE)).Times(1)
		.WillOnce(Return(WAIT_OBJECT_0)); // Event signalled
	EXPECT_DESTRUCTOR_CALLS();

	svr->start();

	svr->test_setThread(NULL);
}}


TEST_F(ServerTest, testStop_ThrowsIfNotStarted) {{
	InSequence s;
	EXPECT_CONSTRUCTOR_CALLS();
	auto_drop<Server> svr(new Server(&winApi, &sm, &windowThread, &cs, &e));

	EXPECT_CALL(cs, enter()).Times(1);
	EXPECT_CALL(cs, leave()).Times(1);
	EXPECT_DESTRUCTOR_CALLS();

	ASSERT_THROW(svr->stop(), exception);
}}

TEST_F(ServerTest, testStop_CleanUpIfThreadIsDead) {{
	InSequence s;
	EXPECT_CONSTRUCTOR_CALLS();
	auto_drop<Server> svr(new Server(&winApi, &sm, &windowThread, &cs, &e));
	
	EXPECT_CALL(cs, enter()).Times(1);
	EXPECT_CALL(cs, leave()).Times(1);
	EXPECT_CALL(thread, isAlive()).Times(1)
		.WillOnce(Return(false));
	EXPECT_CALL(cs, enter()).Times(1);
	EXPECT_CALL(cs, leave()).Times(1);
	EXPECT_DESTRUCTOR_CALLS();

	thread.grab(); // дропнет в cleanup
	svr->test_setThread(&thread);

	svr->stop();

	ASSERT_EQ(1, thread.getRefCount());
}}

TEST_F(ServerTest, testStop_Ok) {{
	InSequence s;
	EXPECT_CONSTRUCTOR_CALLS();
	auto_drop<Server> svr(new Server(&winApi, &sm, &windowThread, &cs, &e));
	EXPECT_CALL(cs, enter()).Times(1);
	EXPECT_CALL(cs, leave()).Times(1);
	EXPECT_CALL(thread, isAlive()).Times(1)
		.WillOnce(Return(true));
	EXPECT_CALL(windowThread, getWindowController()).Times(1)
		.WillOnce(Return(&controller));
	EXPECT_CALL(controller, close()).Times(1);
	EXPECT_DESTRUCTOR_CALLS();

	svr->test_setThread(&thread);
	svr->stop();
	svr->test_setThread(NULL);
}}

TEST_F(ServerTest, testJoin_ThrowsIfNotStarted) {{
	InSequence s;
	EXPECT_CONSTRUCTOR_CALLS();
	auto_drop<Server> svr(new Server(&winApi, &sm, &windowThread, &cs, &e));
	EXPECT_CALL(cs, enter()).Times(1);
	EXPECT_CALL(cs, leave()).Times(1);
	EXPECT_DESTRUCTOR_CALLS();

	ASSERT_THROW(svr->join(), exception);
}}

TEST_F(ServerTest, testJoin_Ok) {{
	InSequence s;
	EXPECT_CONSTRUCTOR_CALLS();
	auto_drop<Server> svr(new Server(&winApi, &sm, &windowThread, &cs, &e));
	svr->test_setThread(&thread);
	EXPECT_CALL(cs, enter()).Times(1);
	EXPECT_CALL(cs, leave()).Times(1);
	EXPECT_CALL(thread, join()).Times(1);
	EXPECT_CALL(cs, enter()).Times(1);
	EXPECT_CALL(cs, leave()).Times(1);
	EXPECT_DESTRUCTOR_CALLS();

	thread.grab(); // дропнет после выхода из join
	svr->join();
	ASSERT_EQ(1, thread.getRefCount());
	ASSERT_EQ((IThread*)NULL, svr->test_getThread());
}}

TEST_F(ServerTest, testRegisterService_ThrowsIfNotStarted) {{
	InSequence s;
	EXPECT_CONSTRUCTOR_CALLS();

	auto_drop<Server> svr(new Server(&winApi, &sm, &windowThread, &cs, &e));

	EXPECT_CALL(cs, enter()).Times(1);
	EXPECT_CALL(cs, leave()).Times(1);
	EXPECT_DESTRUCTOR_CALLS();

	ASSERT_THROW(svr->registerService("foo", &handler), exception);
}}

TEST_F(ServerTest, testRegisterService_Ok) {{
	InSequence s;
	EXPECT_CONSTRUCTOR_CALLS();

	auto_drop<Server> svr(new Server(&winApi, &sm, &windowThread, &cs, &e));

	EXPECT_CALL(cs, enter()).Times(1);
	EXPECT_CALL(cs, leave()).Times(1);
	EXPECT_CALL(e, reset()).Times(1);
	EXPECT_CALL(windowThread, getWindowController()).Times(1)
		.WillOnce(Return(&controller));
	EXPECT_CALL(sm, add(StrEq("foo"), &handler)).Times(1)
		.WillOnce(Return(123));
	EXPECT_CALL(controller, registerService(123)).Times(1);
	EXPECT_CALL(e, wait()).Times(1);
	EXPECT_DESTRUCTOR_CALLS();

	svr->test_setThread(&thread);

	svr->registerService("foo", &handler);

	svr->test_setThread(NULL);
}}

TEST_F(ServerTest, testUnregisterService_ThrowsIfNotStarted) {{
	InSequence s;
	EXPECT_CONSTRUCTOR_CALLS();

	auto_drop<Server> svr(new Server(&winApi, &sm, &windowThread, &cs, &e));

	EXPECT_CALL(cs, enter()).Times(1);
	EXPECT_CALL(cs, leave()).Times(1);
	EXPECT_DESTRUCTOR_CALLS();

	ASSERT_THROW(svr->unregisterService("foo"), exception);
}}

TEST_F(ServerTest, testUnregisterService_Ok) {{
	InSequence s;
	EXPECT_CONSTRUCTOR_CALLS();

	auto_drop<Server> svr(new Server(&winApi, &sm, &windowThread, &cs, &e));

	EXPECT_CALL(cs, enter()).Times(1);
	EXPECT_CALL(cs, leave()).Times(1);
	EXPECT_CALL(e, reset()).Times(1);
	EXPECT_CALL(windowThread, getWindowController()).Times(1)
		.WillOnce(Return(&controller));
	EXPECT_CALL(sm, getId(StrEq("foo"))).Times(1)
		.WillOnce(Return(543));
	EXPECT_CALL(controller, unregisterService(543)).Times(1);
	EXPECT_CALL(e, wait()).Times(1);
	EXPECT_DESTRUCTOR_CALLS();

	svr->test_setThread(&thread);

	svr->unregisterService("foo");

	svr->test_setThread(NULL);
}}

TEST_F(ServerTest, testGetInstance_ReturnsExistingInstance) {{
	InSequence s;
	EXPECT_CONSTRUCTOR_CALLS();
	auto_drop<Server> svr(new Server(&winApi, &sm, &windowThread, &cs, &e));
	EXPECT_CALL(winApi, createMutex(StrEq(SERVER_MUTEX))) 
		.Times(1)
		.WillOnce(Return(&mutex)); // called from setInstance
	mutex.grab();
	EXPECT_CALL(winApi, createMutex(StrEq(SERVER_MUTEX))) 
		.Times(1)
		.WillOnce(Return(&mutex)); // called from getInstance
	mutex.grab();
	EXPECT_DESTRUCTOR_CALLS();

	Server::setInstance(svr);

	ASSERT_EQ(svr.get(), Server::getInstance());
	ASSERT_EQ(2, svr->getRefCount());
	svr->drop();

	ASSERT_EQ(2, mutex.getRefCount()); // остался 1 лишний на деструктор
}}

TEST_F(ServerTest, testGetInstance) {{
	// TODO: протестить конструкцию объекта.
}}

	} // end namespace ddesvr
} // end namespace aquila