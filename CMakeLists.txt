cmake_minimum_required(VERSION 3.10)

# Project name
project(PokerHelper)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the GoogleTest directory
add_subdirectory(googletest)

# Include directories
include_directories(src)

# Source files
set(SOURCES src/main.cpp src/Player.cpp src/game.cpp)

# Add the main executable
add_executable(main ${SOURCES})

# Add the test executable
add_executable(test tests/test_player.cpp src/Player.cpp)

# Link GoogleTest to the test executable
target_link_libraries(test gtest gtest_main)

