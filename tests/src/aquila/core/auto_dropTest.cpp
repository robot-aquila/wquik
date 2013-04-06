#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/core/auto_drop.h"
#include "aquila/core/IReferenceCounted.h"

using namespace std;
using namespace testing;

namespace aquila {
	namespace core {

class auto_dropTest : public ::testing::Test {
protected:
	IReferenceCounted* object;

	virtual void SetUp() {
		object = new IReferenceCounted();
		object->grab();
	}

	virtual void TearDown() {
		if ( object != 0 ) {
			delete object;
		}
	}

	void testDestructor_Helper() {
		ASSERT_EQ(2, object->getRefCount()); // счетчик сылок
		auto_drop<IReferenceCounted> ref(object);
		ASSERT_EQ(2, object->getRefCount()); // ... не измен€етс€
	}

};


TEST_F(auto_dropTest, testDestructor_Ok) {
	testDestructor_Helper(); // локальный указатель должен был вызвать drop
	ASSERT_EQ(1, object->getRefCount());
}

TEST_F(auto_dropTest, testDestructor_NotInitialized) {
	auto_drop<IReferenceCounted> ref;
}

TEST_F(auto_dropTest, testOperator_Pointer_Ok) {
	auto_drop<IReferenceCounted> ref(object);
	ref->grab();
	ASSERT_EQ(3, object->getRefCount());
}

TEST_F(auto_dropTest, testGet) {
	auto_drop<IReferenceCounted> ref;
	ASSERT_EQ(0, ref.get());
	ref = object;
	ASSERT_EQ(object, ref.get());
}

TEST_F(auto_dropTest, testOperator_Pointer_ThrowsIfNotInitialized) {
	auto_drop<IReferenceCounted> ref;
	try {
		ref->grab();
		ADD_FAILURE() << "Expected exception: std::exception";
	} catch ( std::exception& e ) {
		ASSERT_EQ((string)"Pointer not initialized", e.what());
		SUCCEED();
	} catch ( ... ) {
		FAIL() << "Uncaught exception";
	}
}

TEST_F(auto_dropTest, testOperator_Assign_Ok) {
	auto_drop<IReferenceCounted> ref;
	ref = object;
	ref->grab();
	ASSERT_EQ(3, object->getRefCount());
}

TEST_F(auto_dropTest, testOperator_Assign_ThrowsIfAssigned) {
	auto_drop<IReferenceCounted> ref;
	ref = object;
	try {
		ref = object;
		ADD_FAILURE() << "expected exception: std::exception";
	} catch ( std::exception& e ) {
		ASSERT_EQ((string)"Pointer already assigned", e.what());
		SUCCEED();
	} catch ( ... ) {
		FAIL() << "Uncaught exception";
	}
}

TEST_F(auto_dropTest, testCopyConstructor) {
	auto_drop<IReferenceCounted> ref1(object);
	auto_drop<IReferenceCounted> ref2(ref1);

	ASSERT_EQ(3, object->getRefCount());

	//ref2 = ref1; // ошибка компил€ции
}

TEST_F(auto_dropTest, testOperator_Pointer) {
	auto_drop<IReferenceCounted> ref1(object);
	IReferenceCounted* ptr = ref1;
}

	} // end namespace core
} // end namespace aquila
