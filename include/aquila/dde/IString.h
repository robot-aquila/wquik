/**
 * ============================================================================
 * 2011/07/08
 * $Id: IString.h 101 2011-08-11 18:37:57Z whirlwind $
 * Juno
 * ============================================================================
 */
#pragma once
#include <windows.h>
#include <string>
#include "aquila/core/IReferenceCounted.h"

using namespace aquila::core;

namespace aquila {
	namespace dde {

class IInstance;

/**
 * ��������� ��������� �������� DDE ������.
 * �������������:
 *		compareTo
 *		keep
 */
class IString : public IReferenceCounted {
public:

	IString() { }

	virtual ~IString() { }

	/**
	 * �������� ���������� ������.
	 */
	virtual HSZ getHandle() const=0;

	/**
	 * �������� ������ � ����������� ����.
	 */
	virtual std::string getString()=0;

	/**
	 * �������� ��������� ������.
	 */
	virtual int getCodePage() const=0;

	/**
	 * �������� ��������� DDE.
	 */
	virtual IInstance* getInstance()=0;

};

	} // end namespace dde
} // end namespace aquila