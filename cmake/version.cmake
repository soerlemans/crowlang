# Generate the version information from the cmake project version.

# Create version header
configure_file(
	${PROJECT_SOURCE_DIR}/src/version.hpp.in
	${PROJECT_SOURCE_DIR}/src/version.hpp
)
