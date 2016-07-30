#include <iostream>
#include "exercises/test.hpp"

using namespace std;


GTEST_API_ int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}