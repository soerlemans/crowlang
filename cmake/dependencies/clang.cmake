# Libclang (Clang compiler library interface):
message(STATUS "[+] Finding Clang.")
find_package(
	Clang
	CONFIG
	REQUIRED
)

message(STATUS "Found CLang ${CLANG_PACKAGE_VERSION}")
message(STATUS "Using ClangConfig.cmake in: ${CLANG_DIR}")
message(STATUS "dirs: ${CLANG_INCLUDE_DIRS}")

include_directories(SYSTEM ${CLANG_INCLUDE_DIRS})
add_definitions(${CLANG_DEFINITIONS_LIST})

# set(CLANG_LIBS
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
# )

# Link libraries:
target_link_libraries(
	${PROJECT_NAME}
	${CLANG_LIBS}
)
