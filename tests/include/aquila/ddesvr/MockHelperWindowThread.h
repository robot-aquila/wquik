/**
 * ============================================================================
 * 2011/08/03
 * $Id: MockHelperWindowThread.h 96 2011-08-11 17:36:58Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/ddesvr/IHelperWindowThread.h"

namespace aquila {
	namespace ddesvr {

class MockHelperWindowThread : public IHelperWindowThread {
public:

	virtual ~MockHelperWindowThread() { }

	MOCK_METHOD0(run, DWORD());
	MOCK_METHOD0(getWindowController, IHelperWindowController*());
	MOCK_METHOD0(getWindow, IHelperWindow*());

};

	} // end namespace ddesvr
} // end namespace aquila
