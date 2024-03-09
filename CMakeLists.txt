# Set minimum CMake version.
cmake_minimum_required(VERSION 3.22)

# Define the project.
project(
	crow
	VERSION 0.4.0
	DESCRIPTION "Compiler for crowlang."
	LANGUAGES CXX C
)

# Set the targets
include(cmake/targets.cmake)

# Define the executable for the crow compiler.
add_library(${TARGET_CROW_LIB} STATIC)
add_executable(${TARGET_CROW})

# Configure include-what-you-use.
#include(cmake/iwyu.cmake)

set_target_properties(
	${TARGET_CROW}
	PROPERTIES
	EXPORT_COMPILE_COMMANDS ON
)

# Configure the compiler.
include(cmake/compiler.cmake)

# Configure include-what-you-use.
#include(cmake/clang-tidy.cmake)

# Generate the definitions header.
include(cmake/definitions.cmake)

# Add dependencies.
include(cmake/dependencies.cmake)

# Compile sources.
add_subdirectory(src)
target_link_libraries(${TARGET_CROW} ${TARGET_CROW_LIB})

# Build tests.
if(DEFINED BUILD_CROW_TESTS)
include(cmake/dependencies/catch2.cmake)

add_subdirectory(tests)
endif(DEFINED BUILD_CROW_TESTS)
