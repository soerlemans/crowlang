# Libclang (Clang compiler library interface):
message(STATUS "[+] Finding Clang.")

find_package(
	Clang
	17.0.6
	CONFIG
	REQUIRED
)

message(STATUS "Found CLang ${CLANG_PACKAGE_VERSION}")
message(STATUS "Using ClangConfig.cmake in: ${CLANG_DIR}")

# Required setup:
include_directories(SYSTEM ${CLANG_INCLUDE_DIRS})
add_definitions(${CLANG_DEFINITIONS_LIST})

set(CLANG_LIBS
    clangFrontend
    clangBasic
    clangCodeGen
    clangDriver
    clangLex
    clangParse
    clangSema
    clangAST
    clangAnalysis
    clangRewriteFrontend
    clangRewrite
    clangEdit
    clangASTMatchers
    clangTooling
)

# Link libraries:
target_link_libraries(
	${TARGET_CROW_LIB}
	PUBLIC ${CLANG_LIBS}
)
