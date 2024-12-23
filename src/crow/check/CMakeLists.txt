# Add source files
target_sources(${TARGET_CROW_LIB} PRIVATE
   type_promoter.cpp
   env_state.cpp
   symbol_helper.cpp
   type_checker.cpp
)

# Add subdirectories
add_subdirectory(symbol)
add_subdirectory(symbol_table)
