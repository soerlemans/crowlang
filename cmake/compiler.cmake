# Configure the compiler settings.

# Set some compiler options:
set_target_properties(
	${PROJECT_NAME}
	PROPERTIES
	CXX_STANDARD 23
	CXX_COMPILER "g++"
	C_COMPILER "gcc"
)

# Define DEBUG macro if build type is Debug
target_compile_definitions(${PROJECT_NAME} PRIVATE
  $<$<CONFIG:Debug>:DEBUG>
)

# Compiler flags:
target_compile_options(${PROJECT_NAME} PRIVATE
  -Wall
  -Wextra
  -pedantic
)

