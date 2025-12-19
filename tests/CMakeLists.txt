# Add source files:
target_sources(${TARGET_CROW} PRIVATE
	benchmark.cpp
)

# Add directorie:
add_subdirectory(pratt_parser)
add_subdirectory(visitor)
