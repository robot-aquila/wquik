/**
 * ============================================================================
 * 2011/08/01
 * $Id: MockConversation.h 189 2012-01-30 16:03:21Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/dde/IConversation.h"

namespace aquila {
	namespace dde {

class MockConversation : public IConversation {
public:
	virtual ~MockConversation() { }

	MOCK_METHOD0(getHandle, HCONV());
	MOCK_METHOD0(getInstance, IInstance*());
	MOCK_METHOD0(getServiceName, string());
	MOCK_METHOD0(getTopic, string());

};

	} // end namespace dde
} // end namespace aquila