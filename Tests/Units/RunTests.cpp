#include <gtest/gtest.h>


// Point d'entr�e principal pour gTest
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}