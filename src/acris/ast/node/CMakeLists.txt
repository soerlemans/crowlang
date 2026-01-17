# Add sources:
target_sources(${TARGET_ACRIS_LIB} PRIVATE
  list.cpp
)

if(NOT DEFINED ACRIS_CI_BUILD)
  # Included a lot, rarely changes.
  # Keep commented out for now.
  # target_precompile_headers(${TARGET_ACRIS_LIB} PRIVATE
  #   include_nodes.hpp
  # )
endif()

# Add subdirectories:
add_subdirectory(control)
add_subdirectory("function")
add_subdirectory(lvalue)
add_subdirectory(meta)
add_subdirectory(node_traits)
add_subdirectory(operators)
add_subdirectory(packaging)
add_subdirectory(user_types)
add_subdirectory(builtin_types)
