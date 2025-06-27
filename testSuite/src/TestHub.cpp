#include "testSuiteHeader.hpp"

std::string ufit_dir_path = "$TEST_TARGET/$TEST_TARGET_NAME/";

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    // Run all tests
    return RUN_ALL_TESTS();
}
