/**
 * ============================================================================
 * 2011/07/29
 * $Id: ServiceMap.cpp 190 2012-01-30 18:34:54Z whirlwind $
 * ============================================================================
 */

#include "aquila/ddesvr/ServiceMap.h"
#include "aquila/core/Lock.h"

using namespace aquila::core;

namespace aquila {
	namespace ddesvr {

ServiceMap::ServiceMap(ICriticalSection* pCs)
  : cs(pCs),
	lastId(0)
{
}

ServiceMap::~ServiceMap() {
	removeAll();
}

long ServiceMap::add(string name, ICallbackHandler* pHandler) {
	Lock lock(cs);
	IdMap::const_iterator i = idByName.find(name);
	if ( i != idByName.end() ) {
		throw std::exception("Service already exists");
	}
	lastId ++;
	long id = lastId;
	handlerById[id] = (ICallbackHandler*)pHandler->grab();
	nameById[id] = name;
	idByName[name] = id;
	return id;
}

bool ServiceMap::has(string name) {
	Lock lock(cs);
	IdMap::const_iterator i = idByName.find(name);
	return i == idByName.end() ? false : true;
}

bool ServiceMap::has(long serviceId) {
	Lock lock(cs);
	NameMap::const_iterator i = nameById.find(serviceId);
	return i == nameById.end() ? false : true;
}

void ServiceMap::remove(string name) {
	Lock lock(cs);
	IdMap::iterator i = idByName.find(name);
	if ( i == idByName.end() ) {
		throw std::exception("ServiceMap::remove(string): Id not found");
	}
	HandlerMap::iterator h = handlerById.find(i->second);
	if ( h == handlerById.end() ) {
		throw std::exception("ServiceMap::remove(string): Handler not found");
	}
	h->second->drop();
	idByName.erase(i);
	handlerById.erase(h);
	nameById.erase(i->second);
}

void ServiceMap::remove(long serviceId) {
	Lock lock(cs);
	HandlerMap::iterator h = handlerById.find(serviceId);
	if ( h == handlerById.end() ) {
		throw std::exception("ServiceMap::remove(long): Handler not found");
	}
	NameMap::iterator n = nameById.find(serviceId);
	if ( n == nameById.end() ) {
		throw std::exception("ServiceMap::remove(long): Name not found");
	}
	h->second->drop();
	idByName.erase(n->second);
	handlerById.erase(h);
	nameById.erase(n);
}

void ServiceMap::removeAll() {
	Lock lock(cs);
	for ( HandlerMap::const_iterator i = handlerById.begin();
		i != handlerById.end(); ++i )
	{
		i->second->drop();
	}
	handlerById.erase(handlerById.begin(), handlerById.end());
	nameById.erase(nameById.begin(), nameById.end());
	idByName.erase(idByName.begin(), idByName.end());
}

string ServiceMap::getName(long serviceId) {
	Lock lock(cs);
	NameMap::const_iterator i = nameById.find(serviceId);
	if ( i == nameById.end() ) {
		throw std::exception("ServiceMap::getName(long): Name not found");
	}
	return i->second;
}

long ServiceMap::getId(string name) {
	Lock lock(cs);
	IdMap::const_iterator i = idByName.find(name);
	if ( i == idByName.end() ) {
		throw std::exception("ServiceMap::getId(string): Id not found");
	}
	return i->second;
}

ICallbackHandler* ServiceMap::get(long serviceId) {
	Lock lock(cs);
	HandlerMap::const_iterator i = handlerById.find(serviceId);
	if ( i == handlerById.end() ) {
		throw std::exception("ServiceMap::get(long): Handler not found");
	}
	return i->second;
}

ICallbackHandler* ServiceMap::get(string name) {
	Lock lock(cs);
	IdMap::const_iterator i = idByName.find(name);
	if ( i == idByName.end() ) {
		throw std::exception("ServiceMap::get(string): Id not found");
	}
	HandlerMap::const_iterator i2 = handlerById.find(i->second);
	if ( i2 == handlerById.end() ) {
		throw std::exception("ServiceMap::get(string): Handler not found");
	}
	return i2->second;
}

ICriticalSection* ServiceMap::getCriticalSection() {
	return cs;
}

	} // end namespace ddesvr
} // end namespace aquila