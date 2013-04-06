/**
 * ============================================================================
 * 2011/08/03
 * $Id: MockHelperWindowController.h 96 2011-08-11 17:36:58Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/ddesvr/IHelperWindowController.h"

namespace aquila {
	namespace ddesvr {

class MockHelperWindowController : public IHelperWindowController {
public:
	virtual ~MockHelperWindowController() { }

	MOCK_METHOD1(registerService, void(long serviceId));
	MOCK_METHOD1(unregisterService, void(long serviceId));
	MOCK_METHOD0(close, void());

};

	} // end namespace ddesvr
} // end namespace aquila