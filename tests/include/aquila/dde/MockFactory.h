/**
 * ============================================================================
 * 2011/08/06
 * $Id: MockFactory.h 96 2011-08-11 17:36:58Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#include "aquila/dde/IFactory.h"

namespace aquila {
	namespace dde {

class MockFactory : public IFactory {
public:
	virtual ~MockFactory() { }
	MOCK_METHOD2(produce, IInstance*(ICallbackHandler* pHandler, int iCodePage));
};

	} // end namespace dde
} // end namespace aquila