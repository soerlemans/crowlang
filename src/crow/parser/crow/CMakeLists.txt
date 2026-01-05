# Add source files.
target_sources(${TARGET_CROW_LIB} PRIVATE
	crow_parser.cpp
)

# Add subdirectories.
add_subdirectory(pratt)
add_subdirectory(type)
add_subdirectory(context)
