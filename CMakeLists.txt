# Set minimum CMake version
# cmake_minimum_required(VERSION 3.25.1)
cmake_minimum_required(VERSION 3.22)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)

# Set the compiler
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

# Define the project
project(newlang
	VERSION 0.0.0
	DESCRIPTION ""
	LANGUAGES CXX
)

# Create version header
configure_file(
	${PROJECT_SOURCE_DIR}/src/version.hpp.in
	${PROJECT_SOURCE_DIR}/src/version.hpp
)

# Define the executable that will be made
add_executable(${PROJECT_NAME})

# Define DEBUG macro if build type is Debug
target_compile_definitions(${PROJECT_NAME} PRIVATE
  $<$<CONFIG:Debug>:DEBUG>
  # $<$<CONFIG:RelWithDebInfo>:DEBUG>
)

# Compiler flags:
target_compile_options(${PROJECT_NAME} PRIVATE
  -Wall
  -Wextra
  -pedantic
)

# Clang-tidy setup
set(CMAKE_CXX_CLANG_TIDY
  clang-tidy;
  -checks=*;
  -header-filter=src/.*;
  -extra-arg=c++2b;
)

# Add dependencies
include(cmake/dependencies.cmake)

# Run CMake in src/ subdirectory
add_subdirectory(src)
