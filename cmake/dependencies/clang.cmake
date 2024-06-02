# Libclang (Clang compiler library interface):
message(STATUS "[+] Finding Clang.")

find_package(
	Clang
	CONFIG
	REQUIRED
)

message(STATUS "Found CLang ${CLANG_PACKAGE_VERSION}")
message(STATUS "Using ClangConfig.cmake in: ${CLANG_DIR}")

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

#   clangTooling
#   clangFrontendTool
#   clangFrontend
#   clangDriver
#   clangSerialization
#   clangCodeGen
#   clangParse
#   clangSema
#   clangStaticAnalyzerFrontend
#   clangStaticAnalyzerCore
#   clangAnalysis
#   clangEdit
#   clangAST
#   clangLex
#   clangBasic
#   clangASTMatchers
#   clangDynamicASTMatchers
#   clangToolingASTDiff
#   clangToolingCore
#   # clangToolingInclusions
#   # clangToolingInclusionsStdlib
#   clangToolingRefactoring
#   clangToolingSyntax
#   clangSupport
#   #clangStaticAnalyzerCheckers
#   #clangARCMigrate
#   clangRewriteFrontend
#   clangRewrite
)

# Link libraries:
target_link_libraries(
	${TARGET_CROW_LIB}
	${CLANG_LIBS}
)
