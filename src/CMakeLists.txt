# Add source files
target_sources(${PROJECT_NAME} PRIVATE
	main.cpp
)

# Add subdirectories
add_subdirectory(debug)

add_subdirectory(token)
