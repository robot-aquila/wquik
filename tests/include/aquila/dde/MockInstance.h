/**
 * ============================================================================
 * 2011/07/18
 * $Id: MockInstance.h 96 2011-08-11 17:36:58Z whirlwind $
 * Juno
 * ============================================================================
 */

#pragma once
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/dde/IInstance.h"
#include <string>

namespace aquila {
	namespace dde {

		class MockInstance : public IInstance {
		public:
			virtual ~MockInstance() { }

			MOCK_METHOD1(createString, IString*(std::string str));
			MOCK_METHOD1(wrapString, IString*(HSZ hsz));
			MOCK_METHOD1(wrapData, IData*(HDDEDATA hData));
			MOCK_METHOD1(wrapConversation, IConversation*(HCONV hConv));
			MOCK_METHOD0(getLastError, int());
			MOCK_METHOD2(nameService, void(IString* name, UINT afCmd));
			MOCK_METHOD0(getId, DWORD());
			MOCK_METHOD0(getCodePage, int());

		};

	} // end namespace dde
} // end namespace aquila