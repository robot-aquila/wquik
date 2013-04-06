/**
 * ============================================================================
 * 2011/07/12
 * $Id: IData.h 101 2011-08-11 18:37:57Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#include <windows.h>
#include "aquila/core/IReferenceCounted.h"

using namespace aquila::core;

namespace aquila {
	namespace dde {

class IInstance;

/**
 * ��������� ����������� �������� ����� ������ DDE.
 */
class IData : public IReferenceCounted {
public:

	IData() { }

	virtual ~IData() { }

	/**
	 * ��������� ������ �������.
	 */
	virtual DWORD getData(LPBYTE dst, DWORD size, DWORD offset)=0;

	/**
	 * �������� ������ ������.
	 */
	virtual DWORD getSize()=0;

	/**
	 * �������� ���������� ������.
	 */
	virtual HDDEDATA getHandle()=0;

	/**
	 * �������� ��������� DDE.
	 */
	virtual IInstance* getInstance()=0;

};

	} // end namespace dde
} // end namespace aquila