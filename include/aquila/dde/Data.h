/**
 * ============================================================================
 * 2011/07/18
 * $Id: Data.h 101 2011-08-11 18:37:57Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#include "aquila/dde/IData.h"
#include "aquila/dde/IInstance.h"
#include "aquila/core/IWinApi.h"
#include "aquila/core/auto_grab.h"

using namespace aquila::core;

namespace aquila {
	namespace dde {

class Data : public IData {
public:

	/**
	 * ����������� �� ������ ������������ DDE-������.
	 *
	 * pInstance - ��������� �������, �������� ����������� ������.
	 * pWinApi - ��������� ������� WinApi-�������.
	 * hData - ���������� ������.
	 */
	Data(IInstance* pInstance, IWinApi* pWinApi, HDDEDATA hData);

	virtual ~Data();

	/**
	 * ��������� ������ �������.
	 */
	DWORD getData(LPBYTE dst, DWORD size, DWORD offset);

	/**
	 * �������� ������ ������.
	 */
	DWORD getSize();

	/**
	 * �������� ���������� ������.
	 */
	HDDEDATA getHandle();

	/**
	 * �������� ��������� �������� DDE.
	 */
	IInstance* getInstance();

	/**
	 * �������� ��������� �������� WinApi-�������.
	 */
	IWinApi* getWinApi();

private:
	auto_grab<IInstance> instance;
	auto_grab<IWinApi> winApi;
	HDDEDATA handle;

};

	} // end namespace dde
} // end namespace aquila