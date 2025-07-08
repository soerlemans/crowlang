# Add source files
target_sources(${TARGET_CROW_LIB} PRIVATE
   type_promoter.cpp
   env_state.cpp
   semantic_checker.cpp
   semantic_checker_helper.cpp
)

# Add subdirectories
add_subdirectory(symbol_table)
