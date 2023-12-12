# Set minimum CMake version
cmake_minimum_required(VERSION 3.22)

# Define the project
project(
	crow
	VERSION 0.4.0
	DESCRIPTION "Compiler for crowlang."
	LANGUAGES CXX C
)

# Define the executable that will be made
add_executable(${PROJECT_NAME})

# Configure include-what-you-use.
#include(cmake/iwyu.cmake)

set_target_properties(
	${PROJECT_NAME}
	PROPERTIES
	EXPORT_COMPILE_COMMANDS ON
)

# Configure the compiler.
include(cmake/compiler.cmake)

# Configure include-what-you-use.
#include(cmake/clang-tidy.cmake)

# Generate the version header.
include(cmake/version.cmake)

# Add dependencies.
include(cmake/dependencies.cmake)

# Run CMake in src/ subdirectory
add_subdirectory(src)
