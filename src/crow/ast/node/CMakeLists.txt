# Add sources:
target_sources(${TARGET_CROW_LIB} PRIVATE
  list.cpp
)

# Add subdirectories:
add_subdirectory(control)
add_subdirectory("function")
add_subdirectory(lvalue)
add_subdirectory(node_traits)
add_subdirectory(operators)
add_subdirectory(packaging)
add_subdirectory(typing)
add_subdirectory(meta)
