# Catch2 (C++ Unit testing framework):
message(STATUS "[+] Fetching Catch2 framework.")

if(DEFINED CROW_BUILD_TESTS)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.6.0
	SYSTEM
)

FetchContent_MakeAvailable(Catch2)

target_link_libraries(
	${TARGET_CROW_TESTS}
	PUBLIC Catch2::Catch2WithMain
)
endif()
