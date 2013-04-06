/**
 * ============================================================================
 * 2011/08/06
 * $Id: Factory.h 101 2011-08-11 18:37:57Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#include "aquila/dde/IFactory.h"
#include "aquila/core/IWinApi.h"
#include "aquila/core/auto_grab.h"

using namespace aquila;
using namespace aquila::core;

namespace aquila {
	namespace dde {

/**
 * Фабрика экземпляра DDE.
 */
class Factory : public IFactory {
public:
	Factory();
	Factory(IWinApi* pWinApi);
	virtual ~Factory();
	IInstance* produce(ICallbackHandler* pHandler, int iCodePage);

private:
	auto_grab<IWinApi> winApi;
};

	} // end namespace dde
} // end namespace aquila