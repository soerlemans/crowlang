# Add source files
target_sources(${TARGET_ACRIS_LIB} PRIVATE
  parser.cpp
  backtrack_guard.cpp
)

# Add subdirectories
add_subdirectory(acris)
