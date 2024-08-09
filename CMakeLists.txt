cmake_minimum_required(VERSION 3.10)  # Minimum CMake version
project(MyProject)  # Name of the project

# Specify C++ standard
set(CMAKE_C_STANDARD 99)

# Include directories
include_directories(include)

# Add executable
add_executable(test_matrix
    src/matrix.c
    tests/test_matrix.c
)

# Optionally add additional compiler flags
target_compile_options(test_matrix PRIVATE -Wall -Werror)
