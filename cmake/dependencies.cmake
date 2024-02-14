# Install and include dependencies required for the project.

# Find libraries
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

include(ExternalProject)

# Rang (terminal control codes library):
message(STATUS "[+] Fetching rang library.")
FetchContent_Declare(
  rang
  GIT_REPOSITORY https://github.com/agauniyal/rang.git
  GIT_TAG v3.2
  GIT_PROGRESS TRUE
	SYSTEM
)

# Tabulate (Terminal table library):
message(STATUS "[+] Fetching tabulate library.")
FetchContent_Declare(
  tabulate
  GIT_REPOSITORY https://github.com/p-ranav/tabulate.git
  GIT_TAG v1.5
  GIT_PROGRESS TRUE
	SYSTEM
)

# Cereal (C++ serialization library):
message(STATUS "[+] Fetching cereal library.")
FetchContent_Declare(
  cereal
  GIT_REPOSITORY git@github.com:USCiLab/cereal.git
  GIT_TAG v1.3.2
  GIT_PROGRESS TRUE
	SYSTEM
)

# Cpptrace (Stacktraces for C++)
message(STATUS "[+] Fetching cpptrace library.")
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

# On windows copy cpptrace.dll to the same directory as the executable for your_target
if(WIN32)
  add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:cpptrace> $<TARGET_FILE_DIR:${PROJECT_NAME}>
  )
endif()

# Make available:
FetchContent_MakeAvailable(rang tabulate cereal cpptrace)

# Pthread support:
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(
	Threads
	REQUIRED
)

# CLI11 (Terminal flag library):
message(STATUS "[+] Finding CLI11 library.")
find_package(
	CLI11
	CONFIG
	REQUIRED
)

# Boost (C++ utility libraries):
message(STATUS "[+] Finding Boost library.")
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
message(STATUS "[+] Finding LLVM.")
find_package(
	LLVM
	16
	CONFIG
	REQUIRED
)

# Required setup:
include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

# LLVM components to use:
llvm_map_components_to_libnames(
	LLVM_LIBS
	support
	core
	irreader
	codegen
)

# Libclang (Clang compiler library interface):
message(STATUS "[+] Finding Clang.")
find_package(
	Clang
	CONFIG
	REQUIRED
)

include_directories(SYSTEM ${CLANG_INCLUDE_DIRS})
add_definitions(${CLANG_DEFINITIONS_LIST})

# Link libraries:
target_link_libraries(
	${PROJECT_NAME}
	rang
	tabulate::tabulate
	cereal
	cpptrace
	Threads::Threads
	CLI11::CLI11
	${LLVM_LIBS}
)
