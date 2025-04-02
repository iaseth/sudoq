cmake_minimum_required(VERSION 3.10)

# Project name
project(sudoq)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(sudoq src/sudoq.cpp)

# Enable compiler warnings for better code quality
target_compile_options(sudoq PRIVATE -Wall -Wextra -Wpedantic)
