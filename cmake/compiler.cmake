# Configure the compiler settings.

# Variables:
set(CMAKE_CXX_WARNING_FLAGS
    "-Wall"
    "-Wextra"
    "-Wpedantic"
    "-Wunused"
    "-Wunused-parameter"
    "-Wunused-variable"
    "-Wunused-function"
    "-Wunused-value"
    "-Wunused-label"
    "-Wunreachable-code"
    "-Wreturn-type"
		# Clang sees multiple if statements with init clause.
		# Where the variable has the same name as shadowing.
		# So until this is fixed it will be disabled.
    # "-Wshadow"
    "-Wconversion"
    "-Wlogical-op"
    "-Wfloat-equal"
    "-Wcast-qual"
    "-Wcast-align"
    "-Wmissing-declarations"
    "-Wmissing-field-initializers"
		# The standard library triggers this warning.
		# So we cannot use it in conjunction.
		# With -Werror.
    # "-Wnull-dereference"
    "-Wundef"
    "-Wunused-but-set-variable"
    "-Wvla"
    "-Wwrite-strings"
)

# Functions:
function(cxx_configure_target T_TARGET)
	# Add DEBUG macro definition for debugging builds.
	target_compile_definitions(${T_TARGET} PRIVATE
		$<$<CONFIG:Debug>:DEBUG>
		$<$<CONFIG:RelWithDebInfo>:DEBUG>
	)

	# All available and default enabled warnings in Gcc/Clang can be listed with:
	# g++ -Q --help=warning | less

	# Set warnings for target.
	target_compile_options(${T_TARGET} PRIVATE
		${CMAKE_CXX_WARNING_FLAGS}
		$<$<CONFIG:Release>:-Werror>
		$<$<CONFIG:RelWithDebInfo>:-Werror>
	)
endfunction()


# Set some compiler options:
set_target_properties(
	${TARGET_CROW}
	${TARGET_CROW_LIB}
	PROPERTIES
	CXX_STANDARD 23
	CXX_COMPILER "clang"
	C_COMPILER "clang"
)

# Configure compiler for targets:
cxx_configure_target(${TARGET_CROW})
cxx_configure_target(${TARGET_CROW_LIB})
#cxx_configure_target(${TARGET_CROW_STDLIB})

# Set the flags for debugging.
set(CMAKE_CXX_FLAGS_DEBUG
	"-g3 -gdwarf"
)

# Make it possible for tests to include sources from the project root.
if(DEFINED CROW_BUILD_TESTS)
target_include_directories(
	${TARGET_CROW_TESTS}
	PUBLIC ${CMAKE_SOURCE_DIR}/src
)
endif()
