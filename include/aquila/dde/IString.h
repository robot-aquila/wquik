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
 * Интерфейс объектной оболочки DDE строки.
 * Нереализованы:
 *		compareTo
 *		keep
 */
class IString : public IReferenceCounted {
public:

	IString() { }

	virtual ~IString() { }

	/**
	 * Получить дескриптор строки.
	 */
	virtual HSZ getHandle() const=0;

	/**
	 * Получить строку в стандартном виде.
	 */
	virtual std::string getString()=0;

	/**
	 * Получить кодировку строки.
	 */
	virtual int getCodePage() const=0;

	/**
	 * Получить экземпляр DDE.
	 */
	virtual IInstance* getInstance()=0;

};

	} // end namespace dde
} // end namespace aquila