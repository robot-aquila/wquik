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
	 * Конструктор на основе существующей DDE-строки.
	 *
	 * При уничтожении экземпляра, DDE-строка не освобождается.
	 *
	 * pInstance - экземпляр сервиса, которому принадлежит строка.
	 * pWinApi - экземпляр обертки WinAPI-функций.
	 * hSz - дескриптор строки.
	 * iCodePage - кодировка строки.
	 */
	String(IInstance* pInstance, IWinApi* pWinApi, HSZ hSz, int iCodePage);

	/**
	 * Конструктор новой строки.
	 *
	 * При уничтожении экземпляра, DDE-строка освобождается.
	 *
	 * pInstance - экземпляр сервиса, которому принадлежит строка.
	 * pWinApi - экземпляр обертки WinAPI-функций.
	 * str - строка.
	 * iCodePage - кодировка строки.
	 *
	 * Выбрасывает исключение, если неудалось создать строку.
	 */
	String(IInstance* pInstance, IWinApi* pWinApi, std::string str,
		int iCodePage) throw (std::exception);

	~String();

	/**
	 * Получить дескриптор строки.
	 */
	HSZ getHandle() const;

	/**
	 * Получить строку в стандартном виде.
	 */
	std::string getString();

	/**
	 * Получить кодировку строки.
	 */
	int getCodePage() const;

	/**
	 * Получить экземпляр инстанса DDE.
	 */
	IInstance* getInstance();

	/**
	 * Получить экземпляр враппера WinApi-функций.
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