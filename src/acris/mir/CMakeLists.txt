# Add source files:
target_sources(${TARGET_ACRIS_LIB} PRIVATE
  mir.cpp
)

# Add subdirectories:
add_subdirectory(mir_builder)
add_subdirectory(mir_pass)
