#include "gtest\gtest.h"
#include "inout.h"

using namespace com_b_velop;

namespace {
	class InOutTest : public ::testing::Test {
	protected:
		InOutTest() {

		}
		virtual ~InOutTest() {

		}
		virtual void SetUpt() {

		}
		virtual void TearDown() {

		}
	};

	TEST_F(InOutTest, BliBlaBlup) {
		EXPECT_EQ(0, 0);
	}
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}