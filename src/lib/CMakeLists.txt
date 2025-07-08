# Add source files.
target_sources(${TARGET_CROW_LIB} PRIVATE
	filesystem.cpp
)

# Add subdirectories.
add_subdirectory(iomanip)
