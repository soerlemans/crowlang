# LLVM (Compiler toolchain libraries):
message(STATUS "[+] Finding LLVM.")
find_package(
	LLVM
	16
	CONFIG
	REQUIRED
)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

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

message(STATUS "llvm: ${LLVM_LIBS}")

target_link_libraries(
	${PROJECT_NAME}
	${LLVM_LIBS}
)
