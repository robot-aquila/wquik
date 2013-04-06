/**
 * ============================================================================
 * 2011/08/06
 * $Id: Factory.cpp 96 2011-08-11 17:36:58Z whirlwind $ Juno
 * ============================================================================
 */

#include "aquila/dde/Factory.h"
#include "aquila/dde/Instance.h"
#include "aquila/core/WinApi.h"

namespace aquila {
	namespace dde {

Factory::Factory()
  : winApi(WinApi::getInstance())
{
	winApi->drop();
}

Factory::Factory(IWinApi* pWinApi)
  : winApi(pWinApi)
{

}

Factory::~Factory() {

}

IInstance* Factory::produce(ICallbackHandler* pHandler, int iCodePage) {
	return new Instance(winApi, pHandler, iCodePage);
}

	} // end namespace dde
} // end namespace aquila