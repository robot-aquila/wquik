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
 * ��������� ��������� �������� ����������� DDE.
 * ������, ������� �� �����������, ��� ��� �� �������������
 * � �������, ����������� ������ �� QUIK-�:
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
	 * �������� ���������� �����������.
	 */
	virtual HCONV getHandle()=0;

	/**
	 * �������� ��������� DDE.
	 */
	virtual IInstance* getInstance()=0;

	/**
	 * �������� ��� �������.
	 */
	virtual string getServiceName()=0;

	/**
	 * �������� �����.
	 */
	virtual string getTopic()=0;

};

	} // end namespace dde
} // end namespace aquila