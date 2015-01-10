// testmain.cpp
//
// ICS 45C Winter 2014
// Project #4: People Just Love to Play with Words
//
// DO NOT MODIFY THIS FILE AT ALL.  Its job is to launch Google Test and run
// any unit tests that you wrote in source files in the "test" directory.

#include <gtest/gtest.h>


int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

