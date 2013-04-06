/**
 * ============================================================================
 * 2011/08/01
 * $Id: MockString.h 96 2011-08-11 17:36:58Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/dde/IString.h"

namespace aquila {
	namespace dde {

class MockString : public IString {
public:
	virtual ~MockString() { }

	MOCK_CONST_METHOD0(getHandle, HSZ());
	MOCK_METHOD0(getString, std::string());
	MOCK_CONST_METHOD0(getCodePage, int());
	MOCK_METHOD0(getInstance, IInstance*());

};

	} // end namespace dde
} // end namespace aquila