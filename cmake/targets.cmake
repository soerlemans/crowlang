# Set the different CMake targets.

# Define the possible targets/builds.
set(TARGET_CROW_BIN "crow")
set(TARGET_CROW_LIB "crowlib")
set(TARGET_CROW_TESTS "crow_tests")

# Conditionally set the main target.
set(TARGET_CROW "crow")
if(DEFINED BUILD_CROW_TESTS)
set(TARGET_CROW ${TARGET_CROW_TESTS})
endif(DEFINED BUILD_CROW_TESTS)
