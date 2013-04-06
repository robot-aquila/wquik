/**
 * ============================================================================
 * 2011/07/24
 * $Id: MockRunnable.h 96 2011-08-11 17:36:58Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/core/IRunnable.h"

namespace aquila {
	namespace core {

class MockRunnable : public IRunnable {
public:

	virtual ~MockRunnable() { }

	MOCK_METHOD0(run, DWORD());
};

	} // end namespace core
} // end namespace aquila
