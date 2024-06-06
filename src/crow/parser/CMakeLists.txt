# Add source files
target_sources(${TARGET_CROW_LIB} PRIVATE
	parser.cpp
)

# Add subdirectories
add_subdirectory(pratt)
add_subdirectory(crow)
