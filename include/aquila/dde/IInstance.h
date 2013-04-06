/**
 * ============================================================================
 * 2011/07/12
 * $Id: IInstance.h 101 2011-08-11 18:37:57Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#include <windows.h>
#include "aquila/core/IReferenceCounted.h"
#include "aquila/dde/IString.h"
#include "aquila/dde/IData.h"
#include "aquila/dde/IConversation.h"

namespace aquila {
	namespace dde {

/**
 * ��������� ��������� �������� ���������� DDE.
 * ������, ������� �� �����������, ��� ��� �� �������������
 * �������� DDE, ����������� � ���� ��������� ������ �� QUIK.
 *	connect
 *	createData
 *	postAdvice
 *	enableCallback
 */
class IInstance : public IReferenceCounted {
public:

	IInstance() { }

	virtual ~IInstance() { }

	/**
	 * ������� ����� DDE ������.
	 *
	 * ������� ������ ������������� ���������� IString ����� 1.
	 * ��������� ����� ��������������� ������ ��� ���������� ��������.
	 */
	virtual IString* createString(std::string str)=0;

	/**
	 * �������� ������������ DDE ������.
	 *
	 * ������������ ��� ������ � ��������� ��������.
	 * ������� ������ ������������� ���������� IString ����� 1.
	 * ��������� ����� ��������������� ������ ��� ���������� ��������.
	 * ���������� NULL, ���� �������� ����� NULL.
	 */
	virtual IString* wrapString(HSZ hsz)=0;

	/**
	 * �������� ������������ DDE ������.
	 *
	 * ������������ ��� ������ � ��������� �������.
	 * ������� ������ ������������� ���������� IData ����� 1.
	 */
	virtual IData* wrapData(HDDEDATA hData)=0;

	/**
	 * �������� ������������ ���������� �����������.
	 *
	 * ������������ ��� ������ � ��������� �������.
	 * ������� ������ ������������� ���������� ����� 1.
	 */
	virtual IConversation* wrapConversation(HCONV hConv)=0;

	/**
	 * �������� ��� ��������� ������.
	 */
	virtual int getLastError()=0;

	/**
	 * ����������������/������� DDE-������.
	 */
	virtual void nameService(IString* name, UINT afCmd)=0;

	/**
	 * �������� ������������� ��������.
	 *
	 * ���������� ������������� ��������, ���������� � ����������
	 * ������ DdeInitialize.
	 */
	virtual DWORD getId()=0;

	/**
	 * �������� ��������� �����.
	 */
	virtual int getCodePage()=0;

};

	} // end namespace dde
} // end namespace aquila
