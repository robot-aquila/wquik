/**
 * ============================================================================
 * 2011/08/15
 * $Id: MockMutex.h 104 2011-08-15 09:47:48Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/core/IMutex.h"

namespace aquila {
	namespace core {

class MockMutex : public IMutex {
public:

	virtual ~MockMutex() { }
	MOCK_METHOD0(getHandle, HANDLE());

};

	} // end namespace core
} // end namespace aquila
