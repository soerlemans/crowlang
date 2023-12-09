# Add source files:
target_sources(${PROJECT_NAME} PRIVATE
	main.cpp
)

# Utilities:
add_subdirectory(debug)
add_subdirectory(container)

# Error handling:
add_subdirectory(exception)

# Lexing phase:
add_subdirectory(token)
add_subdirectory(lexer)

# Parsing phase:
add_subdirectory(ast)
add_subdirectory(parser)

# Program verification phase:
add_subdirectory(typing)
add_subdirectory(check)

# Code generation phase:
add_subdirectory(codegen)
