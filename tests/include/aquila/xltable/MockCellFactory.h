#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/xltable/ICellFactory.h"

namespace aquila {
	namespace xltable {

class MockCellFactory : public ICellFactory {
public:
	virtual ~MockCellFactory(void) { }
	MOCK_METHOD1(createFloat, ICell*(double));
	MOCK_METHOD1(createBoolean, ICell*(bool));
	MOCK_METHOD2(createString, ICell*(const char*,int));
	MOCK_METHOD1(createInteger, ICell*(int));
	MOCK_METHOD0(createError, ICell*());
	MOCK_METHOD0(createBlank, ICell*());
	MOCK_METHOD0(createSkip, ICell*());
};

	} // end namespace xltable
} // end namespace aquila