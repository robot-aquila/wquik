/**
 * ============================================================================
 * 2011/07/12
 * $Id: IServer.h 104 2011-08-15 09:47:48Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#pragma warning(disable:4290)
#include <exception>
#include <string>
#include "aquila/core/IReferenceCounted.h"
#include "aquila/dde/ICallbackHandler.h"

using namespace std;
using namespace aquila::dde;

namespace aquila {
	namespace ddesvr {

class IServer : public IReferenceCounted {
public:
	virtual ~IServer() { }

	/**
	 * Запустить сервер.
	 */
	virtual void start() throw(exception)=0;

	/**
	 * Остановить сервер.
	 */
	virtual void stop() throw(exception)=0;

	/**
	 * Зарегистрировать новый сервис.
	 */
	virtual void registerService(string name, ICallbackHandler* pHandler)
		throw(exception)=0;

	/**
	 * Удалить сервис.
	 */
	virtual void unregisterService(string name) throw(exception)=0;

	/**
	 * Ожидать фактического завершения работы сервера.
	 */
	virtual void join() throw(exception)=0;

};

	} // end namespace ddesvr
} // end namespace aquila