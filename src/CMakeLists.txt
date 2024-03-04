# Add source files:
if(TARGET TARGET_CROW_BIN)
target_sources(${TARGET_CROW_BIN} PRIVATE
	main.cpp
)
endif(TARGET TARGET_CROW_BIN)

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
add_subdirectory(check)

# Code generation phase:
add_subdirectory(codegen)
