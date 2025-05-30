# Add source files
target_sources(${TARGET_CROW_LIB} PRIVATE
	cpp_backend.cpp
	prototype_generator.cpp
	type_variant2cpp_type.cpp
	clang_frontend_invoker.cpp
)

# Add subdirectories
add_subdirectory(interop)
