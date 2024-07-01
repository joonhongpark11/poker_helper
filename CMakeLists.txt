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
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Source files
set(SOURCES src/main.cpp src/Player.cpp src/Game.cpp)

# Add the main executable
add_executable(main ${SOURCES})

# Add the test executables
add_executable(testPlayer tests/test_player.cpp src/Player.cpp src/Game.cpp)
add_executable(testGame tests/test_game.cpp src/Player.cpp src/Game.cpp)

# Link GoogleTest to the test executables
target_link_libraries(testPlayer gtest gtest_main)
target_link_libraries(testGame gtest gtest_main)
