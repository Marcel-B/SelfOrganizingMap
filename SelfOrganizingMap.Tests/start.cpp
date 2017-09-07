#include <gtest/gtest.h>
#include "inout.test.h"
#include "set.test.h"

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}