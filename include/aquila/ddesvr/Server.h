/**
 * ============================================================================
 * 2011/08/03
 * $Id: Server.h 235 2012-07-23 15:52:48Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#pragma warning(disable:4290)
#include "aquila/ddesvr/IServer.h"
#include "aquila/core/auto_grab.h"
#include "aquila/core/IWinApi.h"
#include "aquila/core/ICriticalSection.h"
#include "aquila/core/IEvent.h"
#include "aquila/core/IThread.h"
#include "aquila/ddesvr/IServer.h"
#include "aquila/ddesvr/IServiceMap.h"
#include "aquila/ddesvr/IHelperWindowThread.h"

using namespace aquila::core;

namespace aquila {
	namespace ddesvr {

#define SERVER_MUTEX	"AQUILA_DDESVR_SERVER_MUTEX"

/**
 * ���������� ������ � ������� DDE. ����������������. ��������.
 */
class Server : public IServer {
public:

	/**
	 * �����������:
	 * pWinApi - �������� winapi. 
	 * pServiceMap - ����� �������� ������������ ��� �������� �����������.
	 * pWindowRunnable - ���������� ������ ���������������� ����.
	 * pCriticalSection - ����������� ������.
	 * pEvent - ������ �������.
	 */
	Server(IWinApi* pWinApi,
		   IServiceMap* pServiceMap,
		   IHelperWindowThread* pWindowRunnable,
		   ICriticalSection* pCs,
		   IEvent* pEvent);

public:
	/**
	 * ������ ����� ���������� ��������� �� ������������� ��������� ������� DDE
	 * � ����������� �������� ������ �� �������. ���� ������� ��������� �������
	 * �� ���������, �� ����� ������������ ��������� ������ Server. ������
	 * ����� ����� ������ ����������� ������� ������ �������� ���������� �� 1
	 * ���������� �� ����, ��� �� ���� ��������� ������������� ��� ����������
	 * � ������� ������ setInstance. ��� �������� ���������, ����������� �
	 * ������� ����� ������ ������ ������� ������������ auto_drop ���������.
	 */
	static IServer* getInstance();

	static void setInstance(IServer* pServer);

	virtual ~Server();

	/**
	 * ��������� ������.
	 * ����� ��������� ������� ����� �� ������� ���� �� ����� ������� ������
	 * �� �������� ������� ������� ��� ��������� ����� �� ���������� � �������.
	 * �� ������ ������ ����� ���������� ����������.
	 */
	void start() throw(exception);

	/**
	 * ���������� ������.
	 * ������ ����� ������ ������������� ���������� ������ � �������������
	 * ��������� ������. ��� �������� ������������ ���������� ����������
	 * ������ ������� ������������ ����� join.
	 */
	void stop() throw(exception);

	void registerService(string name, ICallbackHandler* pHandler)
		throw(exception);

	void unregisterService(string name) throw(exception);

	/**
	 * ������� ���������� ������ �������.
	 * ����� ��������� ������� ����� �� ������� ���������� ������ ����������
	 * ������. ����������� ����������, ���� ������ �� �������.
	 */
	void join() throw(exception);

	IWinApi* getWinApi();

	IServiceMap* getServiceMap();

	IHelperWindowThread* getHelperWindowThread();

	/**
	 * ������ ����������� ������ �������������� � ������������.
	 */
	ICriticalSection* getCriticalSection();

	/**
	 * ������ ������� �������������� � ������������.
	 */
	IEvent* getEvent();

	/**
	 * ������ ������ �������������� ��� �������.
	 */
	IThread* getThread();

#ifdef TEST_RUN
	void test_setThread(IThread* pThread) {
		thread = pThread;
	}

	IThread* test_getThread() {
		return thread;
	}
#else
#pragma message("Set TEST_RUN definition to enable additional method(s):")
#pragma message("aquila::ddesvr::Server::test_setThread")
#pragma message("aquila::ddesvr::Server::test_getThread")
#endif

private:
	void cleanUp();
	void start_critical(HANDLE* handles);
	IThread* getThreadThrowIfNotStarted() throw(exception);

private:
	auto_grab<IWinApi> winApi;
	auto_grab<IServiceMap> serviceMap;
	auto_grab<IHelperWindowThread> runnable;
	auto_grab<ICriticalSection> cs;
	auto_grab<IEvent> e;
	IThread* thread;

	static IServer* pInstance;
};

	} // end namespace ddesvr
} // end namespace aquila