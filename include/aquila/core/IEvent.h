/**
 * ============================================================================
 * 2011/07/24
 * $Id: IEvent.h 104 2011-08-15 09:47:48Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#pragma warning(disable:4290)
#include "aquila/core/IReferenceCounted.h"
#include "aquila/core/WinApiErrorException.h"
#include <exception>
#include <windows.h>

namespace aquila {
	namespace core {

/**
 * Интерфейс объектной оболочки события.
 */
class IEvent : public IReferenceCounted {
public:

	IEvent() { }

	virtual ~IEvent() { }

	virtual HANDLE getHandle()=0;

	virtual void pulse() throw (WinApiErrorException)=0;

	virtual void set() throw (WinApiErrorException)=0;

	virtual void reset() throw (WinApiErrorException)=0;

	/**
	 * Ожидать сигнального состояния.
	 * Делегирует вызов WaitForSingleObject.
	 */
	virtual void wait() throw (WinApiErrorException)=0;

};

	} // end namespace core
} // end namespace aquila
