# Set the different CMake targets.

# Define the possible targets/builds.
set(TARGET_CROW_BIN "crow")    # Compiler binary.
set(TARGET_CROW_LIB "crowlib") # Compiler library.

set(TARGET_CROW_STDCROW "stdcrow") # Standard library for generated C++.

set(TARGET_CROW_TESTS "crow_tests") # Unit test binary

# Conditionally set the main target:
set(TARGET_CROW "crow")

# Change the main target if we are building tests:
if(DEFINED CROW_BUILD_TESTS)
	set(TARGET_CROW ${TARGET_CROW_TESTS})
endif()
