/**
 * ============================================================================
 * 2011/07/23
 * $Id: Lock.h 96 2011-08-11 17:36:58Z whirlwind $ Juno
 * Автоматический вход/выход из критической секции.
 * ============================================================================
 */

#pragma once
#include "aquila/core/IReferenceCounted.h"
#include "aquila/core/auto_grab.h"
#include "aquila/core/ICriticalSection.h"

namespace aquila {
	namespace core {

class Lock : public IReferenceCounted {
public:

	Lock(ICriticalSection* pCriticalSection) : cs(pCriticalSection) {
		cs->enter();
	}

	virtual ~Lock() {
		cs->leave();
	}

	ICriticalSection* getCriticalSection() {
		return cs;
	}

private:
	auto_grab<ICriticalSection> cs;
};

	} // end namespace core
} // end namespace aquila