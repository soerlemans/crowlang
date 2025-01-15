# Add source files:
target_sources(${TARGET_CROW_LIB} PRIVATE
  backend_interface.cpp
)

# Add subdirectories:
add_subdirectory(cpp_backend)
add_subdirectory(llvm_backend)
