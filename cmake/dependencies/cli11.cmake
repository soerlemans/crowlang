# CLI11 (Terminal flag library):
message(STATUS "[+] Finding CLI11 library.")

find_package(
	CLI11
	CONFIG
	REQUIRED
)

target_link_libraries(
	${TARGET_CROW_LIB}
	CLI11::CLI11
)
