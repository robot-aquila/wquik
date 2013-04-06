/**
 * ============================================================================
 * 2011/08/03
 * $Id: Server.cpp 512 2013-02-10 02:20:53Z whirlwind $
 * ============================================================================
 */

#include "aquila/core/auto_drop.h"
#include "aquila/core/Lock.h"
#include "aquila/core/WinApi.h"
#include "aquila/dde/Factory.h"
#include "aquila/ddesvr/Server.h"
#include "aquila/ddesvr/ServiceMap.h"
#include "aquila/ddesvr/HelperWindowThread.h"
#include "aquila/ddesvr/HelperWindow.h"
#include "aquila/ddesvr/HelperWindowHandler.h"
#include "aquila/ddesvr/CallbackDispatcher.h"

namespace aquila {
	namespace ddesvr {

IServer* Server::pInstance = NULL;

IServer* Server::getInstance() {
	auto_drop<IWinApi> winApi(WinApi::getInstance());
	auto_drop<IMutex> m(winApi->createMutex(SERVER_MUTEX));
	if ( pInstance != NULL ) {
		return (IServer*)pInstance->grab();
	}

	auto_drop<IFactory> instanceFactory(new Factory());
	auto_drop<IEvent> e(winApi->createEvent(NULL, TRUE, FALSE, NULL));
	auto_drop<ICriticalSection> smCs(winApi->createCriticalSection());
	auto_drop<IServiceMap> sm(new ServiceMap(smCs));
	auto_drop<ICallbackHandler> handler(new CallbackDispatcher(sm, e));
	auto_drop<IHelperWindowHandler> windowHandler
		(new HelperWindowHandler(instanceFactory, sm, handler));
	auto_drop<IHelperWindow> window(new HelperWindow(winApi, windowHandler));
	auto_drop<IHelperWindowThread> windowRunnable(new HelperWindowThread(window, e));
	auto_drop<ICriticalSection> cs(winApi->createCriticalSection());
	
	pInstance = new Server(winApi, sm, windowRunnable, cs, e);
	return pInstance;
}

void Server::setInstance(IServer* pServer) {
	auto_drop<IWinApi> winApi(WinApi::getInstance());
	auto_drop<IMutex> m(winApi->createMutex(SERVER_MUTEX));
	pInstance = pServer;
}

Server::Server(IWinApi* pWinApi,
			   IServiceMap* pServiceMap,
		       IHelperWindowThread* pWindowRunnable,
			   ICriticalSection* pCs,
			   IEvent* pEvent)
  : winApi(pWinApi),
	cs(pCs),
	e(pEvent),
	runnable(pWindowRunnable),
	serviceMap(pServiceMap),
	thread(NULL)
	
{

}

Server::~Server() {
	auto_drop<IMutex> m(winApi->createMutex(SERVER_MUTEX));
	cleanUp();
	if ( pInstance == this ) {
		pInstance = NULL;
	}
}

IThread* Server::getThreadThrowIfNotStarted() {
	cs->enter();
	IThread* pThread = thread;
	cs->leave();
	if ( pThread == NULL ) {
		throw exception("Not started");
	}
	return pThread;
}

void Server::start_critical(HANDLE* handles) {
	Lock lock(cs);
	if ( thread != NULL ) {
		throw exception("Already started");
	}
	thread = winApi->createThread(runnable);
	thread->start();
	handles[0] = e->getHandle();
	handles[1] = thread->getHandle();
}

void Server::start() {
	HANDLE handles[2];
	start_critical(handles);
	if ( winApi->WaitForMultipleObjects(2, handles,
		FALSE, INFINITE) != WAIT_OBJECT_0 )
	{
		cleanUp();
		throw exception("Start thread failed or finished");
	}
	// ����� �����, ������� ����� �� ��������� �������� ��������� �� e->wait()
	// � Server::unregisterService, ������� ������ ��������� � ������ �������
	// ���������������� ��������/��������� ������� � �������. ����������,
	// ��� ������� ������ � ���, ��� ������� ��������� ������� ������� Windows,
	// ������������� � ������ HelperWindow::messageLoop(), ������ ��������
	// �� GetMessage, ��� � ���� ������� �������� � ���������� ���������������
	// ������� �����. ��� ���������, ����� CallbackDispatcher::onUnregister,
	// ������� � ����� ����� ������ ������������� ��� ����� ����� � ����������
	// ���������, �� ������������ � ���������� ����������� ������� e->wait(),
	// � ������� ������� � ����� ������.
	// 
	// ��������� �� ������ ������ ��� ��� �������������� ����� ���� ���������
	// ��� �������, ������ ���� �����. �� ����� ���� ���� �������� � ����.
	// 1. ��������������� ����� ��������������� ����� ������� ����������
	// ������, � ������� ��������� ���� ����������� ��� DDE. ����� ����������
	// ������� � ���������� ��������� � GetMessage ������� ��������� ����������
	// ���� � �������������� �������. ������ ��������, ����� �������
	// ���������� ��� ���������� ����, ��� �������� � ��������� �����
	// ������������������ �������� �� ������������� �������. ��������� ��������
	// ���������� ������� ������� windows �� ��������, ������� �������
	// ������� ������������� ������ ��������. ��� �������, ��������� ���������
	// e->set() ��� ������ ����� � GetMessage, ��� ������ ������� ���
	// ���� ������ ���� � ���������� WM_CREATE...
	//
	// � ����
	::Sleep(1000);
}

void Server::stop() {
	IThread* pThread = getThreadThrowIfNotStarted();
	if ( ! pThread->isAlive() ) {
		cleanUp();
	} else {
		runnable->getWindowController()->close();
	}
}

void Server::join() {
	IThread* pThread = getThreadThrowIfNotStarted();
	pThread->join();
	cleanUp();
}

void Server::registerService(string name, ICallbackHandler* pHandler) {
	getThreadThrowIfNotStarted();
	e->reset();
	runnable->getWindowController()
		->registerService(serviceMap->add(name, pHandler));
	e->wait();
}

void Server::unregisterService(string name) {
	getThreadThrowIfNotStarted();
	e->reset();
	runnable->getWindowController()
		->unregisterService(serviceMap->getId(name));
	e->wait();
}

ICriticalSection* Server::getCriticalSection() {
	return cs;
}

IWinApi* Server::getWinApi() {
	return winApi;
}

IHelperWindowThread* Server::getHelperWindowThread() {
	return runnable;
}

IServiceMap* Server::getServiceMap() {
	return serviceMap;
}

IEvent* Server::getEvent() {
	return e;
}

IThread* Server::getThread() {
	cs->enter();
	IThread* pThread = thread;
	cs->leave();
	return pThread;
}

void Server::cleanUp() {
	Lock lock(cs);
	if ( thread != NULL ) {
		thread->drop();
		thread = NULL;
	}
}

	} // end namespace ddesvr
} // end namespace aquila