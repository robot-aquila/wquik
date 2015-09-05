#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/core/auto_drop.h"
#include "aquila/core/SleshLibrary.h"
#include "core.TestDll.h"

using namespace testing;

namespace aquila {
	namespace core {

typedef void (CALLBACK setValue)(int);
typedef int (CALLBACK getSum)(int);

class SleshLibraryTest : public ::testing::Test {
protected:

	virtual void SetUp() {

	}

	virtual void TearDown() {

	}

};

TEST_F(SleshLibraryTest, testConstructor_ThrowsIfNoDllFile) {
	try {
		auto_drop<SleshLibrary> lib(new SleshLibrary("unexistent.dll"));
		ADD_FAILURE() << "Expected exception: aquila::core::DllException";
	} catch ( DllException& e ) {
		ASSERT_EQ((string)("Module not found: unexistent.dll"), e.what());
		SUCCEED();
	} catch ( ... ) {
		FAIL() << "Uncaught exception";
	}
}

TEST_F(SleshLibraryTest, testConstructor_Ok) {
	try {
		auto_drop<SleshLibrary> lib(new SleshLibrary("core.TestDll.dll"));
	} catch ( DllException& e ) {
		FAIL() << e.what();
	} catch ( ... ) {
		FAIL() << "Uncaught exception";
	}
}

TEST_F(SleshLibraryTest, testDllMainIsCalled) {
	try {
		auto_drop<SleshLibrary> lib(new SleshLibrary("core.TestDll.dll"));
		getSum* getSumPtr = (getSum*)lib->getProcAddress(FUNCTION_NAME_getSum);
		ASSERT_EQ(TEST_PROCESS_ATTACH_MARKER, (*getSumPtr)(0));
	}
	catch (...) {
		FAIL() << "Uncaught exception";
	}
}

TEST_F(SleshLibraryTest, testGetProcAddress) {
	try {
		auto_drop<SleshLibrary> lib(new SleshLibrary("core.TestDll.dll"));
		
		setValue* setValuePtr =
			(setValue*)lib->getProcAddress(FUNCTION_NAME_setValue);
		getSum* getSumPtr =
			(getSum*)lib->getProcAddress(FUNCTION_NAME_getSum);

		ASSERT_NE((setValue*)0, setValuePtr);
		ASSERT_NE((getSum*)0, getSumPtr);
	} catch ( DllException& e ) {
		FAIL() << e.what();
	} catch ( ... ) {
		FAIL() << "Uncaught exception";
	}
}

TEST_F(SleshLibraryTest, testFunctionCall) {
	try {
		auto_drop<SleshLibrary> lib(new SleshLibrary("core.TestDll.dll"));
		setValue* setValuePtr =
			(setValue*)lib->getProcAddress(FUNCTION_NAME_setValue);
		(*setValuePtr)(150);
	} catch ( DllException& e ) {
		FAIL() << e.what();
	} catch ( ... ) {
		FAIL() << "Uncaught exception";
	}
}

TEST_F(SleshLibraryTest, testFunctionsOfDifferentInstances) {
	// разные экземпляры расположены в собственном адресном пространстве,
	// по этому данные внутри них никак не пересекаются.
	try {
		auto_drop<SleshLibrary> lib1(new SleshLibrary("core.TestDll.dll"));
		
		setValue* setValuePtr1 =
			(setValue*)lib1->getProcAddress(FUNCTION_NAME_setValue);
		getSum* getSumPtr1 =
			(getSum*)lib1->getProcAddress(FUNCTION_NAME_getSum);
		
		auto_drop<SleshLibrary> lib2(new SleshLibrary("core.TestDll.dll"));
		setValue* setValuePtr2 =
			(setValue*)lib2->getProcAddress(FUNCTION_NAME_setValue);
		getSum* getSumPtr2 =
			(getSum*)lib2->getProcAddress(FUNCTION_NAME_getSum);

		ASSERT_NE((setValue*)setValuePtr1, setValuePtr2);
		ASSERT_NE((getSum*)getSumPtr1, getSumPtr2);
		
		(*setValuePtr1)(50); // значение хранится в пространстве 1 либы
		(*setValuePtr2)(75); // это значение не затрет предыдущее
		ASSERT_EQ(75, (*getSumPtr1)(25));
		ASSERT_EQ(100,(*getSumPtr2)(25)); // что подтверждается
	} catch ( DllException& e ) {
		FAIL() << "Uncaught exception: " << e.what();
	} catch ( ... ) {
		FAIL() << "Uncaught exception";
	}
}

	} // end namespace core
} // end namespace aquila
