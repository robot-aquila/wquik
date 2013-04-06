/**
 * ============================================================================
 * 2011/08/01
 * $Id: MockData.h 96 2011-08-11 17:36:58Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/dde/IData.h"

namespace aquila {
	namespace dde {

class MockData : public IData {
public:
	virtual ~MockData() { }

	MOCK_METHOD3(getData, DWORD(LPBYTE dst, DWORD size, DWORD offset));
	MOCK_METHOD0(getSize, DWORD());
	MOCK_METHOD0(getHandle, HDDEDATA());
	MOCK_METHOD0(getInstance, IInstance*());

};

	} // end namespace dde
} // end namespace aquila