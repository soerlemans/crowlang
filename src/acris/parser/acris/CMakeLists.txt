# Add source files.
target_sources(${TARGET_ACRIS_LIB} PRIVATE
	acris_parser.cpp
)

# Add subdirectories.
add_subdirectory(pratt)
add_subdirectory(type)
add_subdirectory(context)
