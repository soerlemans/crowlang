# Cereal (C++ serialization library):
message(STATUS "[+] Fetching cereal library.")

# Set options for cereal CMakeLists.txt.
set(JUST_INSTALL_CEREAL ON CACHE BOOL "Only build Cereal.")

FetchContent_Declare(
  cereal
  GIT_REPOSITORY https://github.com/USCiLab/cereal.git
  GIT_TAG v1.3.2
  GIT_PROGRESS TRUE
	CMAKE_ARGS -DJUST_INSTALL_CEREAL=ON # -DSKIP_PORTABILITY_TEST=ON
	SYSTEM
)

FetchContent_MakeAvailable(cereal)

target_link_libraries(
	${TARGET_ACRIS_LIB}
	PUBLIC cereal
)
