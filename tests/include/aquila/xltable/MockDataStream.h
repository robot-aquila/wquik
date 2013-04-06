#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/xltable/IDataStream.h"

namespace aquila {
	namespace xltable {

class MockDataStream : public IDataStream {
public:
	virtual ~MockDataStream(void) { }
	MOCK_METHOD0(getLength, unsigned int());
	MOCK_METHOD0(getOffset, unsigned int());
	MOCK_METHOD0(readByte, BYTE());
	MOCK_METHOD0(readWord, WORD());
	MOCK_METHOD0(readDword, DWORD());
	MOCK_METHOD1(readString, const char*(size_t size));
	MOCK_METHOD0(readFloat, double());
};

	} // end namespace xltable
} // end namespace aquila