#include "set.test.h"
#include <set.h>
#include <gtest/gtest.h>
#include <iostream>

namespace {
	TEST_F(SetTest, SetCtor_TEST) {
		auto set = new com_b_velop::Set();
		EXPECT_TRUE(set != nullptr);
		// delete set;
	}
	// Tests that the Foo::Bar() method does Abc.
	TEST_F(SetTest, does_split_values_split_TEST) {
		auto set = new com_b_velop::Set();
		set->InitValues(100, 5);

		auto nset = set->SplitValues(1);
		EXPECT_EQ(nset->rows, 1);
		delete nset;
		delete set;
	}
}