# Add source files
target_sources(${TARGET_CROW_LIB} PRIVATE
	pratt_parser.cpp
)

# Add subdirectories
add_subdirectory(binding)
