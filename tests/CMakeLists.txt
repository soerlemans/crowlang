# Add source files:
target_sources(${TARGET_CROW} PRIVATE
	benchmark.cpp
)

# Add directories:
add_subdirectory(visitor)
add_subdirectory(parser)
