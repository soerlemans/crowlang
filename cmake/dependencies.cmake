# Find libraries
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

include(ExternalProject)

# Rang (terminal goodies library):
FetchContent_Declare(
  rang
  GIT_REPOSITORY https://github.com/agauniyal/rang.git
  GIT_TAG v3.2
  GIT_PROGRESS TRUE
	SYSTEM
)

# Tabulate (Terminal table library):
FetchContent_Declare(
  tabulate
  GIT_REPOSITORY https://github.com/p-ranav/tabulate.git
  GIT_TAG v1.5
  GIT_PROGRESS TRUE
	SYSTEM
)

# Cpptrace ()
FetchContent_Declare(
  cpptrace
  GIT_REPOSITORY https://github.com/jeremy-rifkin/cpptrace.git
  GIT_TAG v0.2.1
	SYSTEM
)

add_compile_definitions(
  CPPTRACE_UNWIND_WITH_UNWIND
  CPPTRACE_GET_SYMBOLS_WITH_LIBDWARF
)

set(CMAKE_CXX_FLAGS_DEBUG
	"-g3 -gdwarf"
)

# On windows copy cpptrace.dll to the same directory as the executable for your_target
if(WIN32)
  add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:cpptrace> $<TARGET_FILE_DIR:${PROJECT_NAME}>
  )
endif()

# Make available:
FetchContent_MakeAvailable(rang tabulate cpptrace)

# Pthread support:
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(
	Threads
	REQUIRED
)

# CLI11 (Terminal flag library):
find_package(
	CLI11
	CONFIG
	REQUIRED
)

# Boost (C++ utility libraries):
find_package(
	Boost
	1.74
	COMPONENTS program_options
	REQUIRED
)

include_directories(
	SYSTEM
	${Boost_INCLUDE_DIR}
)

# LLVM (Compiler toolchain libraries):
find_package(
	LLVM
	16
	CONFIG
	REQUIRED
)

include_directories(
	SYSTEM
	${LLVM_INCLUDE_DIRS}
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
	cpptrace
	Threads::Threads
	CLI11::CLI11
	${LLVM_LIBS}
)
