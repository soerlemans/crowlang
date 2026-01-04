# Add sources:
target_sources(${TARGET_CROW_LIB} PRIVATE
  list.cpp
)

if(NOT DEFINED CROW_CI_BUILD)
  # Includes a lot, rarely changes.
  target_precompile_headers(${TARGET_CROW_LIB} PRIVATE
    include_nodes.hpp
  )
endif()

# Add subdirectories:
add_subdirectory(control)
add_subdirectory("function")
add_subdirectory(lvalue)
add_subdirectory(meta)
add_subdirectory(node_traits)
add_subdirectory(operators)
add_subdirectory(packaging)
add_subdirectory(typing)
