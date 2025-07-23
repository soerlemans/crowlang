# Add source files
target_sources(${TARGET_CROW_LIB} PRIVATE
   type_promoter.cpp
   symbol_env_state.cpp
   semantic_checker.cpp
)

# Add subdirectories
add_subdirectory(symbol_table)
