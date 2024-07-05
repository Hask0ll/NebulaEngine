#include <gtest/gtest.h>


// Point d'entrée principal pour gTest
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}