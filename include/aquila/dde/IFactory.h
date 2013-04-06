/**
 * ============================================================================
 * 2011/08/06
 * $Id: IFactory.h 101 2011-08-11 18:37:57Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#include "aquila/core/IReferenceCounted.h"
#include "aquila/dde/IInstance.h"
#include "aquila/dde/ICallbackHandler.h"

namespace aquila {
	namespace dde {

/**
 * Интерфейс фабрики экземпляра DDE.
 */
class IFactory : public IReferenceCounted {
public:
	virtual ~IFactory() { }
	virtual IInstance* produce(ICallbackHandler* pHandler, int iCodePage)=0;
};

	} // end namespace dde
} // end namespace aquila