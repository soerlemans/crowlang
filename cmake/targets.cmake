# Set the different CMake targets.

# Define the possible targets/builds.
set(TARGET_CROW_BIN "crow")
set(TARGET_CROW_LIB "crowlib")

set(TARGET_CROW_STDLIB "stdcrowlib")

set(TARGET_CROW_TESTS "crow_tests")

# Conditionally set the main target:
set(TARGET_CROW "crow")

# Change the main target if we are building tests.
if(DEFINED CROW_BUILD_TESTS)
set(TARGET_CROW ${TARGET_CROW_TESTS})
endif()
