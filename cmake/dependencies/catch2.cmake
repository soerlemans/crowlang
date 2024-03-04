# Catch2 (C++ Unit testing framework):
message(STATUS "[+] Fetching Catch2 framework.")

if(DEFINED TESTS)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0
)

FetchContent_MakeAvailable(Catch2)

target_link_libraries(
	${PROJECT_NAME}
	Catch2::Catch2WithMain
	cereal
)
endif(DEFINED TESTS)
