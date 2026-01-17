# Configure include-what-you-use.

find_program(
	IWYU_PATH
	NAMES iwyu include-what-you-use
	REQUIRED
)

# FIXME: IWYU only works when set globally?
set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE ${IWYU_PATH})
set(CMAKE_C_INCLUDE_WHAT_YOU_USE ${IWYU_PATH})

# set_target_properties(
# 	${TARGET_ACRIS_LIB}
# 	PROPERTIES
# 	CXX_INCLUDE_WHAT_YOU_USE ${IWYU_PATH}
# 	C_INCLUDE_WHAT_YOU_USE ${IWYU_PATH}
# )
