# Add source files
target_sources(${PROJECT_NAME}
	PRIVATE
	parser.cpp
)

# Add subdirectories
add_subdirectory(pratt)
add_subdirectory(crow)
