/**
 * ============================================================================
 * 2011/07/27
 * $Id: IHelperWindowController.h 101 2011-08-11 18:37:57Z whirlwind $ Juno
 * ============================================================================
 */
#pragma once
#pragma warning(disable:4290)
#include <windows.h>
#include "aquila/core/IReferenceCounted.h"
#include "aquila/core/WinApiErrorException.h"

using namespace aquila::core;

namespace aquila {
	namespace ddesvr {

/**
 * ��������� ����������� ���������������� ����. ���������� ������������
 * ��� ���������� ��������������� �����.
 */
class IHelperWindowController : public IReferenceCounted {
public:

	IHelperWindowController() { }

	virtual ~IHelperWindowController() { }

	/**
	 * ���������������� ������ � �������� ���������������.
	 * ������ ����� ���������� ����� ������ onRegisterService �����������
	 * ������� ����. ���� ����� ����� ���� ������ �� ������ ������,
	 * �� ��������� ������� ����� ��������� � ������ ����, ��� ���������
	 * ��������� ������� "��� ������ �� ������ ������", �������������
	 * ����������� DDE.
	 * @serviceId - ������������� �������
	 * @throws WinApiErrorException - � ������ ������ WinAPI
	 */
	virtual void
		registerService(long serviceId) throw (WinApiErrorException)=0;

	/**
	 * ������� ������ � ��������� ���������������.
	 * ������ ����� ���������� ����� ������ onUnregisterService �����������
	 * ������� ����. ��� �� ��� � ����� ����������� �������, ���� ����� �����
	 * ���� ������ �� ������ ������.
	 * @serviceId - ������������� �������
	 * @throws WinApiErrorException - � ������ ������ WinAPI
	 */
	virtual void
		unregisterService(long serviceId) throw (WinApiErrorException)=0;

	/**
	 * ��������� ������.
	 * ����� ������� ������ ���������� �������� ��������� � �������������
	 * ������ ��������� ���������� ������ ���������������� ����. ���� �����
	 * ����� ���� ������ �� ������ ������.
	 * @throws WinApiErrorException - ������ �������� ���������
	 * @throws HelperWindowException - ������ ���� �� ������
	 */
	virtual void close() throw (WinApiErrorException)=0;

};

	} // end namespace ddesvr
} // end namespace aquila