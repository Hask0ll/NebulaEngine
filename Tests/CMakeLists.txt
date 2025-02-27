cmake_minimum_required(VERSION 3.16)
project(NebulaEngineTests VERSION 1.0.0 LANGUAGES CXX)

# Fetch GoogleTest
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
FetchContent_MakeAvailable(googletest)

find_package(fmt CONFIG REQUIRED)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(
        ${CMAKE_SOURCE_DIR}/NebulaEngine/include
        ${gtest_SOURCE_DIR}/include
)

# Find all test source files
file(GLOB_RECURSE TEST_SOURCES
        "${CMAKE_SOURCE_DIR}/Tests/Units/*.cpp"
)

# Create the test executable
add_executable(NebulaEngineTests ${TEST_SOURCES})

# Link against Nebula Engine and GoogleTest
target_link_libraries(NebulaEngineTests
        PRIVATE
        NebulaEngine
        gtest
        gtest_main
        fmt::fmt
)

# Set output directory
set_target_properties(NebulaEngineTests PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Enable testing
enable_testing()

# Add a test target
add_test(
        NAME NebulaEngineTests
        COMMAND NebulaEngineTests
)