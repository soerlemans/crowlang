# CLI11 (Terminal flag library):
message(STATUS "[+] Finding CLI11 library.")
find_package(
	CLI11
	CONFIG
	REQUIRED
)

target_link_libraries(
	${PROJECT_NAME}
	CLI11::CLI11
)
