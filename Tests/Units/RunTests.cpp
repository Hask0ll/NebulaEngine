#include "Nebula.h"
#include <gtest/gtest.h>

TEST(Nebula, Application)
{
	// Initialize logging before tests run
	Nebula::Log::Init();

	// Print test banner
	std::cout << "====================================" << std::endl;
	std::cout << "Running Nebula Engine Tests" << std::endl;
	std::cout << "====================================" << std::endl;

	// Initialize Google Test
	::testing::InitGoogleTest();

	// Run the tests
	int result = RUN_ALL_TESTS();

	// Clean up
	Nebula::Log::Shutdown();
}

Nebula::Application* Nebula::CreateApplication() {
	return nullptr;
}
