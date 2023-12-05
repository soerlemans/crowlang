# Configure clang-tidy.

# Clang-tidy is processing dependencies and failing
find_program(
	CLANG_TIDY_PATH
	NAMES clang-tidy
	REQUIRED
)

set(
	CLANG_TIDY_COMMAND
	${CLANG_TIDY_PATH};
	-header-filter=src/.*;
	-extra-arg=-std=c++2b;
)
# -checks=*;

set_target_properties(
	${PROJECT_NAME}
	PROPERTIES
	CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}"
)
