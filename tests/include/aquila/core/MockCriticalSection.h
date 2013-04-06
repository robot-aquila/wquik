/**
 * ============================================================================
 * 2011/07/23
 * $Id: MockCriticalSection.h 96 2011-08-11 17:36:58Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/core/ICriticalSection.h"

namespace aquila {
	namespace core {

class MockCriticalSection : public ICriticalSection {
public:

	virtual ~MockCriticalSection() { }

	MOCK_METHOD0(enter, void());
	MOCK_METHOD0(leave, void());
};

	} // end namespace core
} // end namespace aquila
