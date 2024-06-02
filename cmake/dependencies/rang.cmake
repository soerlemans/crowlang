# Rang (terminal control codes library):
message(STATUS "[+] Fetching rang library.")

FetchContent_Declare(
  rang
  GIT_REPOSITORY https://github.com/agauniyal/rang.git
  GIT_TAG        v3.2
  GIT_PROGRESS TRUE
	SYSTEM
)

FetchContent_MakeAvailable(rang)

target_link_libraries(
	${TARGET_CROW_LIB}
	rang
)
