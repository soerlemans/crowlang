# Cereal (C++ serialization library):
message(STATUS "[+] Fetching cereal library.")

FetchContent_Declare(
  cereal
  GIT_REPOSITORY https://github.com/USCiLab/cereal.git
  GIT_TAG v1.3.2
  GIT_PROGRESS TRUE
	CMAKE_ARGS -DJUST_INSTALL_CEREAL=ON # -DSKIP_PORTABILITY_TEST=ON
	SYSTEM
)

FetchContent_MakeAvailable(cereal)

# Set options for cereal CMakeLists.txt.
set(JUST_INSTALL_CEREAL ON CACHE BOOL "Only build Cereal.")
set(SKIP_PORTABILITY_TEST OFF CACHE BOOL "Skip portability (32 bit) tests.")
set(BUILD_DOC OFF CACHE BOOL "Dont build documentation.")
set(BUILD_SANDBOX OFF CACHE BOOL "Dont build sandbox examples.")
set(SKIP_PERFORMANCE_COMPARISON ON CACHE BOOL "Skip building performance sandbox comparison.")

target_link_libraries(
	${TARGET_CROW_LIB}
	PUBLIC cereal
)
