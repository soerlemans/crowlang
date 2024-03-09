# Generate useful definitions for the sources.

# Definitions to include:
set(crow_PROJECT_ROOT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
set(crow_PROJECT_SRC_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(crow_PROJECT_TEST_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/test")

# Create the definitions header:
configure_file(
	${PROJECT_SOURCE_DIR}/src/definitions.hpp.in
	${PROJECT_SOURCE_DIR}/src/definitions.hpp
)
