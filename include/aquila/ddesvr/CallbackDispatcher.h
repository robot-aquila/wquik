/**
 * ============================================================================
 * 2011/08/01
 * $Id: CallbackDispatcher.h 104 2011-08-15 09:47:48Z whirlwind $ Juno
 * ============================================================================
 */
#pragma once
#include "aquila/dde/ICallbackHandler.h"
#include "aquila/ddesvr/IServiceMap.h"
#include "aquila/core/auto_grab.h"
#include "aquila/core/IEvent.h"

using namespace aquila::dde;
using namespace aquila::core;

namespace aquila {
	namespace ddesvr {

/**
 * ��������� �������� �������, ��������� ����� �������� �������������� ������,
 * ����������� �� DDE, ��������������� ������������. ����� �����, ���������
 * ��������� �������� ��������������� ������ � ����� �������� ����� ���������
 * ���������� onUnregister.
 */
class CallbackDispatcher : public ICallbackHandler {
public:

	/**
	 * �����������.
	 * pServiceMap - ��������� ����� ��������
	 * pEvent - ��������� ������� ������������ ��� ������������ ���������
	 * ��������������� ������� ��� �����������/������������� ��������.
	 */
	CallbackDispatcher(IServiceMap* pServiceMap, IEvent* pEvent);

	virtual ~CallbackDispatcher();

	/**
	 * ��������� ��������������� ���������������� ����������� ����������.
	 */
	bool onConnect(IString* topic, IString* service, PCONVCONTEXT pContext,
		bool isSameInstance);

	/**
	 * ��������� ��������������� ���������������� ����������� ����������.
	 */
	void onConnectConfirm(IConversation* conv, IString* topic,
		IString* service, bool isSameInstance);

	/**
	 * ��������� ��������������� ���������������� ����������� ����������.
	 */
	void onDisconnect(IConversation* conv, bool isSameInstance);

	/**
	 * ��������� ��������������� ���������������� ����������� ����������.
	 */
	int onPoke(UINT uFmt, IConversation* conv, IString* topic, IString* item,
		IData* data);

	/**
	 * ��������� ��������������� ���������������� ����������� ����������
	 * � ������������� � ���������� ��������� ����������� ��������.
	 */
	void onRegister(IString* service, IString* instanceName);

	/**
	 * ��������� ��������������� ���������������� ����������� ����������,
	 * ������� ������ �� ����� �������� � ������������� � ���������� ���������
	 * ����������� ��������.
	 */
	void onUnregister(IString* service, IString* instanceName);

	/**
	 * �������� ����� ��������.
	 */
	IServiceMap* getServiceMap();

	/**
	 * �������� �������.
	 */
	IEvent* getEvent();

private:
	auto_grab<IServiceMap> serviceMap;
	auto_grab<IEvent> e;

};

	} // end namespace ddesvr
} // end namespace aquila