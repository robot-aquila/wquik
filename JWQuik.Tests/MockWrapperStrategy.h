#pragma once

#include <jwquik/JavaWrapper.h>

using namespace jwquik;

class MockWrapperStrategy : public IWrapperStrategy {
public:
	virtual ~MockWrapperStrategy(void){}

	MOCK_METHOD0(drop, bool());
	MOCK_METHOD0(grab, void*());

	MOCK_METHOD1(produce, IJavaHelper*(JNIEnv*));
	MOCK_METHOD1(produce, IJavaHelper*(JavaVM*));
	MOCK_METHOD1(init, void(JavaVM*));
	MOCK_METHOD1(free, void(JavaVM*));
};
