#include <inout.h>
#include <gtest/gtest.h>
#include "inout.test.h"
#include <vector>
#include <iostream>

namespace {
	// Tests that the Foo::Bar() method does Abc.
	TEST_F(InOutTest, inout_ctor_TEST) {
		std::vector<double> values = { 1, 10 };
		auto actual = com_b_velop::InOut::scale_values(values);
		EXPECT_DOUBLE_EQ(0.01, actual[0]);
		EXPECT_DOUBLE_EQ(0.99, actual[1]);
	}
}
