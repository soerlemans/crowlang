# Add source files
target_sources(${TARGET_CROW_LIB} PRIVATE
  parser.cpp
  backtrack_guard.cpp
)

# Add subdirectories
add_subdirectory(type)
add_subdirectory(pratt)
add_subdirectory(crow)
