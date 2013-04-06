/**
 * ============================================================================
 * 2011/08/03
 * $Id: MockHelperWindow.h 104 2011-08-15 09:47:48Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/ddesvr/IHelperWindow.h"

namespace aquila {
	namespace ddesvr {

class MockHelperWindow : public IHelperWindow {
public:
	virtual ~MockHelperWindow() { }

	MOCK_METHOD0(registerClass, void());
	MOCK_METHOD0(createWindow, IHelperWindowController*());
	MOCK_METHOD0(unregisterClass, void());
	MOCK_METHOD0(messageLoop, void());

};

	} // end namespace ddesvr
} // end namespace aquila