#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/xltable/ICellAggregator.h"

namespace aquila {
	namespace xltable {

class MockCellAggregator : public ICellAggregator {
public:
	virtual ~MockCellAggregator(void) { }
	MOCK_METHOD0(getCellCount, unsigned int());
	MOCK_METHOD1(getCell, ICell*(unsigned int));
	MOCK_METHOD1(addFloat, unsigned int(double));
	MOCK_METHOD1(addBoolean, unsigned int(bool));
	MOCK_METHOD2(addString, unsigned int(const char*,int));
	MOCK_METHOD1(addInteger, unsigned int(int));
	MOCK_METHOD0(addError, unsigned int());
	MOCK_METHOD0(addBlank, unsigned int());
	MOCK_METHOD0(addSkip, unsigned int());
};

	} // end namespace xltable
} // end namespace aquila