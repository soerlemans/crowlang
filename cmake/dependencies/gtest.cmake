# Google test (C++ Unit testing framework):
message(STATUS "[+] Fetching Gtest.")

if(DEFINED ACRIS_BUILD_TESTS)
FetchContent_Declare(
  GTest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.17.0
  SYSTEM
)

FetchContent_MakeAvailable(GTest)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "Respect our C runtime settings." FORCE)

target_link_libraries(
	${TARGET_ACRIS_TESTS}
    PUBLIC GTest::gtest_main
)
endif()
