# CMakeList.txt : CMake project for Nebula, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Set the project name
project ("NebulaEngine")

# Packages
find_package(fmt CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add source to this project's executable.
add_executable (Nebula "Nebula.cpp" "Nebula.h")
add_executable (NebulaTests "Tests/Units/RunTests.cpp" "Nebula.h")

# Link libraries
target_link_libraries(Nebula PRIVATE fmt::fmt)
target_link_libraries(NebulaTests PRIVATE fmt::fmt GTest::gtest GTest::gtest_main)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Nebula PROPERTY CXX_STANDARD 20)
endif()

# Add tests to CTest
enable_testing()
add_test(NAME NebulaTests COMMAND NebulaTests)

# TODO: Add tests and install targets if needed.
