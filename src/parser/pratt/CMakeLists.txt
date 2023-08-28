# Add source files
target_sources(${PROJECT_NAME}
	PRIVATE
	pratt_parser.cpp
)

# Add subdirectories
add_subdirectory(binding)
