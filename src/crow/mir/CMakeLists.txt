# Add source files:
target_sources(${TARGET_CROW_LIB} PRIVATE
  mir.cpp
)

# Add subdirectories:
add_subdirectory(mir_builder)
add_subdirectory(mir_pass)
