/**
 * ============================================================================
 * 2011/08/12
 * $Id: ServiceHandler.h 543 2013-02-25 06:35:27Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#include <string>
#include "aquila/jddesvr/Table.h"

using namespace std;

namespace aquila {
	namespace jddesvr {

/**
 * Адаптированный для использования на стороне Java
 * базовый обработчик событий DDE-сервиса.
 */
class ServiceHandler {
public:
	ServiceHandler(string serviceName) : name(serviceName) {

	}

	virtual ~ServiceHandler() {

	}

	virtual string getName() {
		return name;
	}

	virtual bool onConnect(string topic) {
		return false;
	}

	virtual void onConnectConfirm(string topic) {

	}

	virtual bool onRawData(string topic, string item,
		char* dataBuffer, int size)
	{
		return false;
	}

	virtual void onData(Table* table) {

	}

	virtual void onDisconnect(string topic) {

	}

	virtual void onRegister() {

	}

	virtual void onUnregister() {

	}

private:
	string name;
};

	} // end namespace jddesvr
} // end namespace aquila