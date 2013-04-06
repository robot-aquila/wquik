/**
 * ============================================================================
 * 2011/07/23
 * $Id: ICriticalSection.h 96 2011-08-11 17:36:58Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#include "aquila/core/IReferenceCounted.h"

using namespace aquila;

namespace aquila {
	namespace core {

class ICriticalSection : public IReferenceCounted {
public:
	ICriticalSection() { }
	virtual ~ICriticalSection() { }
	virtual void enter()=0;
	virtual void leave()=0;
};

	} // end namespace core
} // end namespace aquila