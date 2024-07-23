# Toml++ (C++ toml config file parser/serializer):
message(STATUS "[+] Fetching toml++.")

FetchContent_Declare(
    tomlplusplus
    GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
    GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(tomlplusplus)

target_link_libraries(
	${TARGET_CROW_LIB}
	PUBLIC tomlplusplus::tomlplusplus
)
