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
add_subdirectory(diagnostic)

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

# Type model for semantic, and codegen:
add_subdirectory(types)

# Symbol table and symbol registers:
add_subdirectory(symbol_table)

# Semantic analysis:
add_subdirectory(semantic)

# CrowLang Intermediate Representation generation:
add_subdirectory(mir)

# Code generation phase:
add_subdirectory(codegen)
