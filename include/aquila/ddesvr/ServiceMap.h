/**
 * ============================================================================
 * 2011/07/29
 * $Id: ServiceMap.h 101 2011-08-11 18:37:57Z whirlwind $
 * ============================================================================
 */

#pragma once
#include "aquila/core/auto_grab.h"
#include "aquila/ddesvr/IServiceMap.h"
#include <map>

using namespace std;

namespace aquila {
	namespace ddesvr {

/**
 * Карта сервисов. Карта сервисов обеспечивает доступ к обработчику
 * транзакций на основе строкового или целочисленного идентификатора.
 */
class ServiceMap : public IServiceMap {
public:

	ServiceMap(ICriticalSection* pCs);

	virtual ~ServiceMap();

	long add(string name, ICallbackHandler* pHandler) throw (exception);

	bool has(string name);

	bool has(long serviceId);

	void remove(string name) throw (exception);

	void remove(long serviceId) throw (exception);

	void removeAll();

	string getName(long serviceId) throw (exception);

	long getId(string name) throw (exception);

	ICallbackHandler* get(long serviceId) throw (exception);

	ICallbackHandler* get(string name) throw (exception);

	ICriticalSection* getCriticalSection();

private:
	typedef map<long, ICallbackHandler*> HandlerMap;
	typedef map<long, string> NameMap;
	typedef map<string, long> IdMap;

	long lastId;
	auto_grab<ICriticalSection> cs;
	HandlerMap handlerById;
	NameMap nameById;
	IdMap idByName;

};

	} // end namespace ddesvr
} // end namespace aquila