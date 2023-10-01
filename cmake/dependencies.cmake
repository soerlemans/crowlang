# Find libraries
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

# Rang (terminal goodies library):
FetchContent_Declare(
  rang
  GIT_REPOSITORY https://github.com/agauniyal/rang.git
  GIT_TAG v3.2
  GIT_PROGRESS TRUE)

# Tabulate (Terminal table library):
FetchContent_Declare(
  tabulate
  GIT_REPOSITORY https://github.com/p-ranav/tabulate.git
  GIT_TAG v1.5
  GIT_PROGRESS TRUE)

# Backward (stack trace library):
# FetchContent_Declare(
# 	backward
#   GIT_REPOSITORY https://github.com/bombela/backward-cpp
#   GIT_TAG v1.6
# 	GIT_PROGRESS TRUE)

# Make available:
# FetchContent_MakeAvailable(rang tabulate backward)
FetchContent_MakeAvailable(rang tabulate)

# Pthread support:
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# CLI11 (Terminal flag library):
find_package(CLI11 CONFIG REQUIRED)

# Boost (C++ utility libraries):
find_package(Boost 1.74 COMPONENTS program_options REQUIRED )

# LLVM (Compiler toolchain libraries):
find_package(LLVM 16 CONFIG REQUIRED)

include_directories(SYSTEM
	${LLVM_INCLUDE_DIRS}
	${Boost_INCLUDE_DIR}
)
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

llvm_map_components_to_libnames(LLVM_LIBS
	support
	core
	irreader
	codegen
)

# Link libraries:
target_link_libraries(
	${PROJECT_NAME}
	rang
	tabulate::tabulate
	Threads::Threads
	CLI11::CLI11
	${LLVM_LIBS}
)
