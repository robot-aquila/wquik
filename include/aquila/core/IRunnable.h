/**
 * ============================================================================
 * 2011/07/23
 * $Id: IRunnable.h 96 2011-08-11 17:36:58Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#include <windows.h>
#include "aquila/core/IReferenceCounted.h"

namespace aquila {
	namespace core {

class IRunnable : public IReferenceCounted {
public:
	IRunnable() { }
	virtual ~IRunnable() { }
	virtual DWORD run()=0;
};

	} // end namespace core
} // end namespace aquila