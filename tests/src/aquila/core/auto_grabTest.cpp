#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/core/auto_grab.h"
#include "aquila/core/IReferenceCounted.h"

using namespace std;
using namespace testing;

namespace aquila {
	namespace core {

class auto_grabTest : public ::testing::Test {
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
		auto_grab<IReferenceCounted> ref(object);
		ASSERT_EQ(3, object->getRefCount()); // ... увеличилс€
	}

};


TEST_F(auto_grabTest, testDestructor_Ok) {
	testDestructor_Helper(); // локальный указатель должен был вызвать grab
	ASSERT_EQ(2, object->getRefCount());
}

TEST_F(auto_grabTest, testDestructor_NotInitialized) {
	auto_grab<IReferenceCounted> ref;
}

TEST_F(auto_grabTest, testOperator_Pointer_Ok) {
	auto_grab<IReferenceCounted> ref(object);
	ref->grab();
	ASSERT_EQ(4, object->getRefCount());
}

TEST_F(auto_grabTest, testGet) {
	auto_grab<IReferenceCounted> ref;
	ASSERT_EQ(0, ref.get());
	ref = object;
	ASSERT_EQ(object, ref.get());
}

TEST_F(auto_grabTest, testOperator_Pointer_ThrowsIfNotInitialized) {
	auto_grab<IReferenceCounted> ref;
	try {
		ref->grab(); // должен вызвать исключение, так как нет указател€
					 // на реальный объект
		ADD_FAILURE() << "Expected exception: std::exception";
	} catch ( std::exception& e ) {
		ASSERT_EQ((string)"Pointer not initialized", e.what());
		SUCCEED();
	} catch ( ... ) {
		FAIL() << "Uncaught exception";
	}
}

TEST_F(auto_grabTest, testOperator_Assign_Ok) {
	auto_grab<IReferenceCounted> ref;
	ref = object;
	ASSERT_EQ(3, object->getRefCount()); // увеличивает счетчик
}

TEST_F(auto_grabTest, testOperator_Assign_ThrowsIfAssigned) {
	auto_grab<IReferenceCounted> ref;
	ref = object;
	try {
		ref = object;
		ASSERT_EQ(3, object->getRefCount());
		ADD_FAILURE() << "expected exception: std::exception";
	} catch ( std::exception& e ) {
		ASSERT_EQ((string)"Pointer already assigned", e.what());
		SUCCEED();
	} catch ( ... ) {
		FAIL() << "Uncaught exception";
	}
}

TEST_F(auto_grabTest, testCopyConstructor) {
	auto_grab<IReferenceCounted> ref1(object);
	auto_grab<IReferenceCounted> ref2(ref1);

	ASSERT_EQ(4, object->getRefCount());

	//ref2 = ref1; // ошибка компил€ции
}

TEST_F(auto_grabTest, testOperator_Pointer) {
	auto_grab<IReferenceCounted> ref1(object);
	IReferenceCounted* ptr = ref1;
}

	} // end namespace core
} // end namespace aquila
