# Set minimum CMake version.
cmake_minimum_required(VERSION 3.22)

# Define the project.
project(
  crow
  VERSION 0.4.0
  DESCRIPTION "Compiler for crowlang."
  LANGUAGES CXX C
)

# Set the target variables.
include(cmake/targets.cmake)

# Define the executable for the crow compiler.
add_library(${TARGET_CROW_LIB} STATIC)
# add_library(${TARGET_CROW_STDLIBCROW} SHARED)
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

# Configure clang-tidy.
include(cmake/clang-tidy.cmake)

# Configure Link time optimization.
include(cmake/lto.cmake)

# Generate the definitions header.
include(cmake/definitions.cmake)

# Add dependencies.
include(cmake/dependencies.cmake)

# Define src/ as include directory.
target_include_directories(
  ${TARGET_CROW_LIB}
  PUBLIC src/
)

# Compile sources.
add_subdirectory(src)
target_link_libraries(
  ${TARGET_CROW}
  PUBLIC ${TARGET_CROW_LIB})

# Build tests:
if(DEFINED CROW_BUILD_TESTS)
  include(cmake/dependencies/gtest.cmake)

  add_subdirectory(tests)
endif()
