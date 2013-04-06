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
	 * Конструктор на основе существующих DDE-данных.
	 *
	 * pInstance - экземпляр сервиса, которому принадлежит строка.
	 * pWinApi - экземпляр обертки WinApi-функций.
	 * hData - дескриптор данных.
	 */
	Data(IInstance* pInstance, IWinApi* pWinApi, HDDEDATA hData);

	virtual ~Data();

	/**
	 * Заполнить буффер данными.
	 */
	DWORD getData(LPBYTE dst, DWORD size, DWORD offset);

	/**
	 * Получить размер данных.
	 */
	DWORD getSize();

	/**
	 * Получить дескриптор данных.
	 */
	HDDEDATA getHandle();

	/**
	 * Получить экземпляр инстанса DDE.
	 */
	IInstance* getInstance();

	/**
	 * Получить экземпляр враппера WinApi-функций.
	 */
	IWinApi* getWinApi();

private:
	auto_grab<IInstance> instance;
	auto_grab<IWinApi> winApi;
	HDDEDATA handle;

};

	} // end namespace dde
} // end namespace aquila