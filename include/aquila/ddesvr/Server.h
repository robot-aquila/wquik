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
 * Реализация фасада к серверу DDE. Потокобезопасный. Синглтон.
 */
class Server : public IServer {
public:

	/**
	 * Конструктор:
	 * pWinApi - оболочка winapi. 
	 * pServiceMap - карта сервисов используется для проброса обработчика.
	 * pWindowRunnable - реализация потока вспомогательного окна.
	 * pCriticalSection - критическая секция.
	 * pEvent - объект события.
	 */
	Server(IWinApi* pWinApi,
		   IServiceMap* pServiceMap,
		   IHelperWindowThread* pWindowRunnable,
		   ICriticalSection* pCs,
		   IEvent* pEvent);

public:
	/**
	 * Данный метод возвращает указатель на установленный экземпляр сервера DDE
	 * с увеличением счетчика ссылок на единицу. Если текущий экземпляр сервера
	 * не определен, то метод инстанцирует экземпляр класса Server. Каждый
	 * вызов этого метода увеличивает счетчик ссылок текущего экземпляра на 1
	 * независимо от того, был ли этот экземпляр инстанцирован или установлен
	 * с помощью метода setInstance. Для хранения указателя, полученного с
	 * помощью этого метода всегда следует использовать auto_drop указатель.
	 */
	static IServer* getInstance();

	static void setInstance(IServer* pServer);

	virtual ~Server();

	/**
	 * Запустить сервер.
	 * Вызов блокирует текущий поток до момента пока не будет получен сигнал
	 * об успешном запуске сервера или серверный поток не завершится с ошибкой.
	 * Во втором случае будет возбуждено исключение.
	 */
	void start() throw(exception);

	/**
	 * Остановить сервер.
	 * Данный метод просто сигнализирует серверному потоку о необходимости
	 * завершить работу. Для ожидания фактического завершения серверного
	 * потока следует использовать метод join.
	 */
	void stop() throw(exception);

	void registerService(string name, ICallbackHandler* pHandler)
		throw(exception);

	void unregisterService(string name) throw(exception);

	/**
	 * Ожидать завершения работы сервера.
	 * Метод блокирует текущий поток до момента завершения работы серверного
	 * потока. Выбрасывает исключение, если сервер не запущен.
	 */
	void join() throw(exception);

	IWinApi* getWinApi();

	IServiceMap* getServiceMap();

	IHelperWindowThread* getHelperWindowThread();

	/**
	 * Объект критической секции инстанцируется в конструкторе.
	 */
	ICriticalSection* getCriticalSection();

	/**
	 * Объект событие инстанцируется в конструкторе.
	 */
	IEvent* getEvent();

	/**
	 * Объект потока инстанцируется при запуске.
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