# Add source files:
target_sources(${TARGET_CROW_LIB} PRIVATE
  clir.cpp
)

# Add subdirectories:
add_subdirectory(clir_builder)
