/**
 * ============================================================================
 * 2011/08/01
 * $Id: MockServiceMap.h 96 2011-08-11 17:36:58Z whirlwind $ Juno
 * ============================================================================
 */

#pragma once
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/ddesvr/IServiceMap.h"

namespace aquila {
	namespace ddesvr {

class MockServiceMap : public IServiceMap {
public:
	virtual ~MockServiceMap() { }

	MOCK_METHOD1(has, bool(string name));
	MOCK_METHOD1(has, bool(long serviceId));
	MOCK_METHOD2(add, long(string name, ICallbackHandler* pHandler));
	MOCK_METHOD1(remove, void(string name));
	MOCK_METHOD1(remove, void(long serviceId));
	MOCK_METHOD0(removeAll, void());
	MOCK_METHOD1(getName, string(long serviceId));
	MOCK_METHOD1(getId, long(string name));
	MOCK_METHOD1(get, ICallbackHandler*(long serviceId));
	MOCK_METHOD1(get, ICallbackHandler*(string name));
	MOCK_METHOD0(getCriticalSection, ICriticalSection*());

};

	} // end namespace ddesvr
} // end namespace aquila