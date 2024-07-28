# CMakeList.txt : CMake project for Nebula, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Properties
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

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
find_package(spdlog CONFIG REQUIRED)

# Add Shared Library
add_library(Nebula SHARED  NebulaEngine/src/Core/Engine.cpp NebulaEngine/src/Logger/Log.cpp)
target_compile_definitions(Nebula PRIVATE NEBULA_EXPORTS)
target_sources(Nebula
  PUBLIC
  FILE_SET HEADERS
  BASE_DIRS
  NebulaEngine/include
  FILES
  NebulaEngine/include/Core/Core.h NebulaEngine/include/Events/ApplicationEvent.h NebulaEngine/include/Window/Window.h NebulaEngine/include/Platforms/Linux/Linux.h 
  NebulaEngine/include/Nebula.h NebulaEngine/include/Core/Application.h NebulaEngine/include/logger/log.h NebulaEngine/include/Events/Event.h NebulaEngine/include/Events/KeyEvent.h NebulaEngine/include/Events/MouseEvent.h
)

# Add source to this project's executable.
add_executable (Game "Game/Game.cpp")
add_executable (NebulaTests "Tests/Units/RunTests.cpp")
target_sources(Nebula
  PUBLIC
  FILE_SET HEADERS
  BASE_DIRS
  spdlog/include
)

# Link libraries
target_link_libraries(Nebula PRIVATE fmt::fmt spdlog::spdlog)
target_link_libraries(Game PRIVATE Nebula)
target_link_libraries(NebulaTests PRIVATE Nebula fmt::fmt GTest::gtest_main)

# Add tests to CTest
enable_testing()
add_test(NAME NebulaTests COMMAND NebulaTests)
