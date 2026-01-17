# Add source files.
target_sources(${TARGET_ACRIS_LIB} PRIVATE
	filesystem.cpp
)

# Add subdirectories.
add_subdirectory(iomanip)
add_subdirectory(stdexcept)
