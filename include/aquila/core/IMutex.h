/** 
 * ============================================================================
 * 2011/08/15
 * $Id: IMutex.h 104 2011-08-15 09:47:48Z whirlwind $ Juno
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

class IMutex : public IReferenceCounted {
public:
	IMutex() { }
	virtual ~IMutex() { };
	virtual HANDLE getHandle()=0;
};

	} // end namespace core
} // end namespace aquila
