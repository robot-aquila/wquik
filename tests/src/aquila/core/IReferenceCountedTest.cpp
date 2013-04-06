#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/core/IReferenceCounted.h"

using namespace testing;

namespace aquila {
	namespace core {

bool destructorCalled = false;

	class IReferenceCountedTest_Class : public IReferenceCounted {
	public:
		virtual ~IReferenceCountedTest_Class() {
			destructorCalled = true;
		}
	};

class IReferenceCountedTest : public ::testing::Test {
protected:
	IReferenceCounted* ref;

	virtual void SetUp() {
		destructorCalled = false;
		ref = 0;
	}

	virtual void TearDown() {
		if ( ref != 0 && ! destructorCalled ) {
			delete ref;
		}
	}

};

TEST_F(IReferenceCountedTest, testConstructor) {
	ref = new IReferenceCountedTest_Class();
	ASSERT_EQ(1, ref->getRefCount());
}

TEST_F(IReferenceCountedTest, testGrab) {
	ref = new IReferenceCountedTest_Class();
	ref->grab();
	ASSERT_EQ(2, ref->getRefCount());
}

TEST_F(IReferenceCountedTest, testDrop) {
	ref = new IReferenceCountedTest_Class();
	ref->drop();
	ASSERT_TRUE(destructorCalled);
}

	} // end namespace core
} // end namespace aquila
