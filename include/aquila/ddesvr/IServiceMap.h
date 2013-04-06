/**
 * ============================================================================
 * 2011/07/29
 * $Id: IServiceMap.h 101 2011-08-11 18:37:57Z whirlwind $
 * ============================================================================
 */

#pragma once
#pragma warning(disable:4290)
#include "aquila/core/IReferenceCounted.h"
#include "aquila/core/ICriticalSection.h"
#include "aquila/dde/ICallbackHandler.h"
#include <exception>
#include <string>

using namespace std;
using namespace aquila::core;
using namespace aquila::dde;

namespace aquila {
	namespace ddesvr {

/**
 * ��������� ����� ��������. ����� �������� ������������ ������ � �����������
 * ���������� �� ������ ���������� ��� �������������� ��������������.
 */
class IServiceMap : public IReferenceCounted {
public:

	/**
	 * ��������� ������� ������� �� ����� �������.
	 */
	virtual bool has(string name)=0;

	/**
	 * ��������� ������� ������� �� �������������� �������.
	 */
	virtual bool has(long serviceId)=0;

	/**
	 * �������� ������. ����������� ����������, ���� ������ � ��������� ������
	 * ��� ���������������.
	 */
	virtual long add(string name, ICallbackHandler* pHandler)
		throw (exception)=0;

	/**
	 * ������� ������ �� �����. ����������� ����������, ���� ������ �
	 * ��������� ������ �� ������.
	 */
	virtual void remove(string name) throw (exception)=0;

	/**
	 * ������� ������ �� ��������������. ����������� ����������, ����
	 * ������ � ��������� ��������������� �� ������.
	 */
	virtual void remove(long serviceId) throw (exception)=0;

	/**
	 * ������� ��� �������.
	 */
	virtual void removeAll()=0;

	/**
	 * �������� ��� ������� �� ��������������. ����������� ����������,
	 * ���� ������ � ��������� ��������������� �� ������.
	 */
	virtual string getName(long serviceId) throw (exception)=0;

	/**
	 * �������� ������������� ������� �� �����. ����������� ����������,
	 * ���� ������ � ��������� ������ �� ������.
	 */
	virtual long getId(string name) throw (exception)=0;

	/**
	 * �������� ����������, ��������������� ������� � ���������
	 * ���������������. ����������� ����������, ���� ������ � ���������
	 * ��������������� �� ������.
	 */
	virtual ICallbackHandler* get(long serviceId) throw (exception)=0;

	/**
	 * �������� ����������, ��������������� �������� � ��������� ������.
	 * ����������� ����������, ���� ������ � ��������� ������ �� ������.
	 */
	virtual ICallbackHandler* get(string name) throw (exception)=0;

	/**
	 * �������� ����������� ������, �������������� ��� ���������� ���
	 * ���������� ��������. ����������� ������ ����� ���� ������������ ���
	 * ����������� ������������������ �������.
	 */
	virtual ICriticalSection* getCriticalSection()=0;

	virtual ~IServiceMap() { }

};

	} // end namespace ddesvr
} // end namespace aquila