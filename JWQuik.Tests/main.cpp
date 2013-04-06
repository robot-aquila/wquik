#include <gtest/gtest.h>
#include "TestEnv.h"

int main( int argc, char* argv[] ) {
	if ( ! TestEnv::init() ) {
		return 1;
	}
	::testing::InitGoogleTest(&argc, argv);
	int res = RUN_ALL_TESTS();
	TestEnv::free();
}
