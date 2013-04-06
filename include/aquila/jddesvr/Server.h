/**
 * ============================================================================
 * 2011/08/12
 * $Id: Server.h 511 2013-02-10 01:44:46Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#pragma warning(disable:4290)
#include "aquila/core/auto_drop.h"
#include "aquila/ddesvr/Server.h"
#include "aquila/jddesvr/CallbackAdapter.h"

namespace aquila {
	namespace jddesvr {

/**
 * Класс-адаптер для класса ddesvr::Server.
 */
class Server {
public:

	Server() : native(aquila::ddesvr::Server::getInstance()) {

	}

	virtual ~Server() {

	}

	void start() throw(std::exception) {
		native->start();
	}

	void stop() throw(std::exception) {
		native->stop();
	}

	void join() throw(std::exception) {
		native->join();
	}

	void registerService(ServiceHandler* service) throw(exception) {
		auto_drop<CallbackAdapter> adapter(new CallbackAdapter(service));
		native->registerService(service->getName(), adapter);
	}

	void unregisterService(ServiceHandler* service) throw(exception) {
		native->unregisterService(service->getName());
	}

private:
	auto_drop<aquila::ddesvr::IServer> native;

};

	} // end namespace jddesvr
} // end namespace aquila