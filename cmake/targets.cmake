# Set the different CMake targets.

# Define the possible targets/builds.
set(TARGET_ACRIS_BIN "acris")    # Compiler binary.
set(TARGET_ACRIS_LIB "acrislib") # Compiler library.

set(TARGET_ACRIS_STDACRIS "stdacris") # Standard library for generated C++.

set(TARGET_ACRIS_TESTS "acris_tests") # Unit test binary

# Conditionally set the main target:
set(TARGET_ACRIS "acris")

# Change the main target if we are building tests:
if(DEFINED ACRIS_BUILD_TESTS)
	set(TARGET_ACRIS ${TARGET_ACRIS_TESTS})
endif()
