# Tabulate (Terminal table library):
message(STATUS "[+] Fetching tabulate library.")
FetchContent_Declare(
  tabulate
  GIT_REPOSITORY https://github.com/p-ranav/tabulate.git
  GIT_TAG v1.5
  GIT_PROGRESS TRUE
	SYSTEM
)

FetchContent_MakeAvailable(tabulate)

target_link_libraries(
	${PROJECT_NAME}
	tabulate::tabulate
)
