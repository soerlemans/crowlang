# Add source files
target_sources(${PROJECT_NAME} PRIVATE
	main.cpp
)

# Add subdirectories
add_subdirectory(debug)
add_subdirectory(container)
add_subdirectory(exception)

add_subdirectory(lexer)
add_subdirectory(token)

add_subdirectory(ast)
add_subdirectory(parser)

add_subdirectory(typing)

add_subdirectory(codegen)
