# Catch2 (C++ Unit testing framework):
message(STATUS "[+] Fetching Catch2 framework.")

if(DEFINED BUILD_CROW_TESTS)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.6.0
)

FetchContent_MakeAvailable(Catch2)

target_link_libraries(
	${TARGET_CROW_TESTS}
	Catch2::Catch2WithMain
)

endif(DEFINED BUILD_CROW_TESTS)
