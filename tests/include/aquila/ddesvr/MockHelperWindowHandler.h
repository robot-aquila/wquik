/**
 * ============================================================================
 * 2011/07/28
 * $Id: MockHelperWindowHandler.h 96 2011-08-11 17:36:58Z whirlwind $
 * Juno
 * ============================================================================
 */

#pragma once
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/ddesvr/IHelperWindowHandler.h"
#include <string>

namespace aquila {
	namespace ddesvr {

class MockHelperWindowHandler : public IHelperWindowHandler {
public:
	virtual ~MockHelperWindowHandler() { }

	MOCK_METHOD0(onBeforeCreate, void());
	MOCK_METHOD0(onCreate, void());
	MOCK_METHOD0(onDestroy, void());
	MOCK_METHOD0(onAfterDestroy, void());
	MOCK_METHOD1(onRegisterService, void(long serviceId));
	MOCK_METHOD1(onUnregisterService, void (long serviceId));

};

	} // end namespace ddesvr
} // end namespace aquila