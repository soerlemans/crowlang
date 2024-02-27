# Cereal (C++ serialization library):
message(STATUS "[+] Fetching cereal library.")
FetchContent_Declare(
  cereal
  GIT_REPOSITORY git@github.com:USCiLab/cereal.git
  GIT_TAG v1.3.2
  GIT_PROGRESS TRUE
	SYSTEM
)

FetchContent_MakeAvailable(cereal)

target_link_libraries(
	${PROJECT_NAME}
	cereal
)
