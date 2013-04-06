/**
 * ============================================================================
 * 2011/08/01
 * $Id: HelperWindowHandler.h 235 2012-07-23 15:52:48Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#include "aquila/core/auto_grab.h"
#include "aquila/dde/IFactory.h"
#include "aquila/ddesvr/IHelperWindowHandler.h"
#include "aquila/ddesvr/IServiceMap.h"

using namespace aquila::dde;

namespace aquila {
	namespace ddesvr {

/**
 * ���������� ������� ���������������� ���� ����������� ������� � ������
 * ��������������� ������� DDE. ��������������� ������ � ����� ������, �� ����
 * �� �������� ����������������.
 */
class HelperWindowHandler : public IHelperWindowHandler {
public:

	/**
	 * pInstanceFactory - ������� DDE-��������.
	 * pMap - ����� �������� ������������ ��� ���������� ������� �� �����
	 * onRegisterService, onUnregisterService � ��� ����������� ����������
	 * ����������.
	 * pCallback - ���������� DDE-���������� ������������ ��� ���������������
	 * DDE-����������.
	 */
	HelperWindowHandler(IFactory* pInstanceFactory,
						IServiceMap* pMap,
						ICallbackHandler* pCallback);

	virtual ~HelperWindowHandler();

	/**
	 * �������� �� ����� �������� �������� ���������� DDE.
	 */
	void onBeforeCreate();

	void onCreate();

	/**
	 * �������� �� ����� �������� �������� ���� ������������������ � �����
	 * ��������.
	 */
	void onDestroy();

	/**
	 * �������� �� ����� �������� �������� ���������� DDE.
	 */
	void onAfterDestroy();

	/**
	 * �������� �� ����� �������� ����� DdeNameService ��� �����������
	 * �������, ��� �������� ������������� ���������� �������������� � �����.
	 */
	void onRegisterService(long serviceId);

	/**
	 * �������� �� ����� �������� ����� DdeNameService ��� �������������
	 * �������, ��� �������� ������������� ���������� �������������� � �����.
	 */
	void onUnregisterService(long serviceId);

	IFactory* getInstanceFactory();

	IServiceMap* getServiceMap();

	ICallbackHandler* getCallbackHandler();

#ifdef TEST_RUN
	void setInstance(IInstance* pInstance) {
		instance = pInstance;
	}

	IInstance* getInstance() {
		return instance;
	}
#else
#pragma message("Set TEST_RUN definition to enable additional method(s):")
#pragma message("aquila::ddesvr::HelperWindowHandler::setInstance")
#pragma message("aquila::ddesvr::HelperWindowHandler::getInstance")
#endif

private:
	IInstance* instance;
	auto_grab<IFactory> factory;
	auto_grab<IServiceMap> serviceMap;
	auto_grab<ICallbackHandler> handler;

};

	} // end namespace ddesvr
} // end namespace aquila