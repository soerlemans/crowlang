# Add source files
target_sources(${PROJECT_NAME} PRIVATE
	main.cpp
)

# Add subdirectories
# Utilities
add_subdirectory(debug)
add_subdirectory(container)
add_subdirectory(exception)

# Lex step
add_subdirectory(token)
add_subdirectory(lexer)

# Parse step
add_subdirectory(ast)
add_subdirectory(parser)

# Verify AST/program step
add_subdirectory(check)

# Generate code step
add_subdirectory(codegen)
