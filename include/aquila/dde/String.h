/**
 * ============================================================================
 * 2011/07/08
 * $Id: String.h 101 2011-08-11 18:37:57Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#pragma warning(disable:4290)
#include "aquila/dde/IString.h"
#include "aquila/dde/IInstance.h"
#include "aquila/core/IWinApi.h"
#include "aquila/core/auto_grab.h"

using namespace aquila::core;

namespace aquila {
	namespace dde {

class String : public IString {
public:

	/**
	 * ����������� �� ������ ������������ DDE-������.
	 *
	 * ��� ����������� ����������, DDE-������ �� �������������.
	 *
	 * pInstance - ��������� �������, �������� ����������� ������.
	 * pWinApi - ��������� ������� WinAPI-�������.
	 * hSz - ���������� ������.
	 * iCodePage - ��������� ������.
	 */
	String(IInstance* pInstance, IWinApi* pWinApi, HSZ hSz, int iCodePage);

	/**
	 * ����������� ����� ������.
	 *
	 * ��� ����������� ����������, DDE-������ �������������.
	 *
	 * pInstance - ��������� �������, �������� ����������� ������.
	 * pWinApi - ��������� ������� WinAPI-�������.
	 * str - ������.
	 * iCodePage - ��������� ������.
	 *
	 * ����������� ����������, ���� ��������� ������� ������.
	 */
	String(IInstance* pInstance, IWinApi* pWinApi, std::string str,
		int iCodePage) throw (std::exception);

	~String();

	/**
	 * �������� ���������� ������.
	 */
	HSZ getHandle() const;

	/**
	 * �������� ������ � ����������� ����.
	 */
	std::string getString();

	/**
	 * �������� ��������� ������.
	 */
	int getCodePage() const;

	/**
	 * �������� ��������� �������� DDE.
	 */
	IInstance* getInstance();

	/**
	 * �������� ��������� �������� WinApi-�������.
	 */
	IWinApi* getWinApi();

private:
	HSZ handle;
	int codePage;
	auto_grab<IInstance> instance;
	auto_grab<IWinApi> winApi;
	bool allocated;

};

	} // end namespace dde
} // end namespace aquila