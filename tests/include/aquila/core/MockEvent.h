/**
 * ============================================================================
 * 2011/08/03
 * $Id: MockEvent.h 104 2011-08-15 09:47:48Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/core/IEvent.h"

namespace aquila {
	namespace core {

class MockEvent : public IEvent {
public:

	virtual ~MockEvent() { }
	MOCK_METHOD0(getHandle, HANDLE());
	MOCK_METHOD0(pulse, void());
	MOCK_METHOD0(set, void());
	MOCK_METHOD0(reset, void());
	MOCK_METHOD0(wait, void());

};

	} // end namespace core
} // end namespace aquila
