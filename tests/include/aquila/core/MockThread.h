/**
 * ============================================================================
 * 2011/08/03
 * $Id: MockThread.h 96 2011-08-11 17:36:58Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/core/IThread.h"

namespace aquila {
	namespace core {

class MockThread : public IThread {
public:

	virtual ~MockThread() { }

	MOCK_METHOD0(start, void());
	MOCK_METHOD0(isAlive, bool());
	MOCK_METHOD0(join, void());
	MOCK_METHOD0(getExitCode, DWORD());
	MOCK_METHOD0(getHandle, HANDLE());
	MOCK_METHOD0(getId, DWORD());

};

	} // end namespace core
} // end namespace aquila
