/**
 * ============================================================================
 * 2011/07/27
 * $Id: IHelperWindowHandler.h 101 2011-08-11 18:37:57Z whirlwind $ Juno
 * ============================================================================
 */
#pragma once
#include "aquila/core/IReferenceCounted.h"

using namespace aquila::core;

namespace aquila {
	namespace ddesvr {

/**
 * ��������� ����������� ������� ���������������� ����.
 * ��� ������ ������� �������������� �� ���������� ������, ��� ���������
 * ������������ ���������� ������ ���� ������� DDE � ������������ �
 * ������������ WinAPI.
 */
class IHelperWindowHandler : public IReferenceCounted {
public:

	IHelperWindowHandler() { }

	virtual ~IHelperWindowHandler() { }

	/**
	 * ����� ���������� � ������ �������� ���� (������� �� WM_NCCREATE).
	 * ������ ����� ������������ ��� �������� �������� DDE.
	 */
	virtual void onBeforeCreate()=0;

	/**
	 * ����� ���������� � ������ �������� ���� (������� �� WM_CREATE).
	 * � ������� ���������� ����� ����� �������������� ����� DdeNameService
	 * ��� ��������� ���� ��������.
	 */
	virtual void onCreate()=0;

	/**
	 * ����� ���������� ����� ����������� ������ ����. ���� �����
	 * �������������� �� ��������� WM_NCDESTROY � ���� �� ��������� WM_CLOSE.
	 * ��� ������� ��� ����, ��� �� �������� ����������� ����������
	 * XTYP_UNREGISTER � ����������� ���������� DDE.
	 */
	virtual void onDestroy()=0;

	/**
	 * ����� ���������� ����� ����������� ����.
	 * ����� ��� ������� ������� ������ ���� �����������.
	 */
	virtual void onAfterDestroy()=0;

	/**
	 * ����� ���������� ��� ������� �� ������ � ����������� ������ �������.
	 * @param serviceId - ������������� �������
	 */
	virtual void onRegisterService(long serviceId)=0;

	/**
	 * ����� ���������� ��� ������� �� ������ �� �������� �������.
	 * @param serviceId - ������������� �������
	 */
	virtual void onUnregisterService(long serviceId)=0;

};

	} // end namespace ddesvr
} // end namespace aquila