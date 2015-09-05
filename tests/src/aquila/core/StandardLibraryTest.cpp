#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/core/auto_drop.h"
#include "aquila/core/StandardLibrary.h"
#include "core.TestDll.h"
#include <string>

using namespace testing;
using namespace std;

namespace aquila {
	namespace core {

typedef void (__stdcall setValue)(int);
typedef int (__stdcall getSum)(int);

class StandardLibraryTest : public ::testing::Test {
protected:

	virtual void SetUp() {

	}

	virtual void TearDown() {

	}

};

TEST_F(StandardLibraryTest, testConstructor_ThrowsIfNoDllFile) {
	try {
		auto_drop<StandardLibrary> lib(new StandardLibrary("unexistent.dll"));
		ADD_FAILURE() << "Expected exception: aquila::core::DllException";
	} catch ( DllException& e ) {
		ASSERT_EQ((string)("Unable to load dll: unexistent.dll"), e.what());
		SUCCEED();
	} catch ( ... ) {
		FAIL() << "Uncaught exception";
	}
}

TEST_F(StandardLibraryTest, testConstructor_Ok) {
	try {
		auto_drop<StandardLibrary> lib(new StandardLibrary("core.TestDll.dll"));
	} catch ( DllException& e ) {
		FAIL() << e.what();
	} catch ( ... ) {
		FAIL() << "Uncaught exception";
	}
}

TEST_F(StandardLibraryTest, testGetProcAddress) {
	try {
		auto_drop<StandardLibrary> lib(new StandardLibrary("core.TestDll.dll"));
		
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

TEST_F(StandardLibraryTest, testDllMainIsCalled) {
	try {
		auto_drop<StandardLibrary> lib(new StandardLibrary("core.TestDll.dll"));
		getSum* getSumPtr = (getSum*)lib->getProcAddress(FUNCTION_NAME_getSum);
		ASSERT_EQ(TEST_PROCESS_ATTACH_MARKER, (*getSumPtr)(0));
	}
	catch (...) {
		FAIL() << "Uncaught exception";
	}
}

TEST_F(StandardLibraryTest, testFunctionsOfDifferentInstances) {
	// разные экземпляры расположены в одном адресном пространстве,
	// по этому данные внутри них пересекаются.
	try {
		auto_drop<StandardLibrary> lib1(new StandardLibrary("core.TestDll.dll"));
		setValue* setValuePtr1 =
			(setValue*)lib1->getProcAddress(FUNCTION_NAME_setValue);
		getSum* getSumPtr1 =
			(getSum*)lib1->getProcAddress(FUNCTION_NAME_getSum);

		auto_drop<StandardLibrary> lib2(new StandardLibrary("core.TestDll.dll"));
		setValue* setValuePtr2 =
			(setValue*)lib2->getProcAddress(FUNCTION_NAME_setValue);
		getSum* getSumPtr2 =
			(getSum*)lib2->getProcAddress(FUNCTION_NAME_getSum);

		ASSERT_EQ((setValue*)setValuePtr1, setValuePtr2);
		ASSERT_EQ((getSum*)getSumPtr1, getSumPtr2);

		(*setValuePtr1)(50); // значение хранится в пространстве 1 либы
		(*setValuePtr2)(75); // это значение затрет предыдущее
		ASSERT_EQ(100, (*getSumPtr1)(25));
		ASSERT_EQ(100, (*getSumPtr2)(25)); // что подтверждается

	} catch ( DllException& e ) {
		FAIL() << e.what();
	} catch ( ... ) {
		FAIL() << "Uncaught exception";
	}
}

	} // end namespace core
} // end namespace aquila
