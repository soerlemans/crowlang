# Find libraries
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

# Tabulate (Terminal table library)
FetchContent_Declare(
  tabulate
  GIT_REPOSITORY https://github.com/p-ranav/tabulate.git
  GIT_TAG v1.5
  GIT_PROGRESS TRUE)

FetchContent_MakeAvailable(tabulate)

# C++ thread support
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# CLI11 (Terminal flag library)
find_package(CLI11 CONFIG REQUIRED)

# Link libraries
target_link_libraries(
	${PROJECT_NAME}
	tabulate::tabulate
	Threads::Threads
	CLI11::CLI11)
