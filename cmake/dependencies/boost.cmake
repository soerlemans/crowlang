# Boost (C++ utility libraries):
message(STATUS "[+] Finding Boost library.")

find_package(
	Boost
	1.74
	COMPONENTS system filesystem program_options
	REQUIRED
)

include_directories(
	SYSTEM
	${Boost_INCLUDE_DIR}
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
)
