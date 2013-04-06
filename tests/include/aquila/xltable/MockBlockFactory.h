#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/xltable/IBlockFactory.h"

namespace aquila {
	namespace xltable {

class MockBlockFactory : public IBlockFactory {
public:
	virtual ~MockBlockFactory(void) { }
	MOCK_METHOD1(produceBlock, IBlock*(unsigned short));
};

	} // end namespace xltable
} // end namespace aquila