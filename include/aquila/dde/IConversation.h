/**
 * ============================================================================
 * 2011/07/12
 * $Id: IConversation.h 189 2012-01-30 16:03:21Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#include <windows.h>
#include <string>
#include "aquila/core/IReferenceCounted.h"

using namespace std;
using namespace aquila::core;

namespace aquila {
	namespace dde {

class IInstance;

/**
 * Интерфейс объектной оболочки подключения DDE.
 * Методы, которые не реализованы, так как не задействованы
 * в сервисе, принимающем данные от QUIK-а:
 *	abandonTransaction
 *	clientTransaction
 *	impersonateClient
 *	queryConvInfo
 *	reconnect
 *	setUserHandle
 */
class IConversation : public IReferenceCounted {
public:

	IConversation() { }

	virtual ~IConversation() { }

	/**
	 * Получить дескриптор подключения.
	 */
	virtual HCONV getHandle()=0;

	/**
	 * Получить экземпляр DDE.
	 */
	virtual IInstance* getInstance()=0;

	/**
	 * Получить имя сервиса.
	 */
	virtual string getServiceName()=0;

	/**
	 * Получить топик.
	 */
	virtual string getTopic()=0;

};

	} // end namespace dde
} // end namespace aquila