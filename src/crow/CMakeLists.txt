# Add source files:
if(TARGET ${TARGET_CROW_BIN})
# Do not add main.cpp to build tree if we are building tests.
target_sources(${TARGET_CROW_BIN} PRIVATE
	main.cpp
)
endif(TARGET ${TARGET_CROW_BIN})

target_sources(${TARGET_CROW} PRIVATE
	banner.cpp
)

# Utilities:
add_subdirectory(debug)
add_subdirectory(container)

# Error handling:
add_subdirectory(exception)

# Handles compiler settings.
add_subdirectory(settings)

# Invokes all the phases:
add_subdirectory(unit)

# Lexing phase:
add_subdirectory(token)
add_subdirectory(lexer)

# Parsing phase:
add_subdirectory(ast)
add_subdirectory(parser)

# Semantic analysis:
add_subdirectory(semantic)

# Code generation phase:
add_subdirectory(codegen)
