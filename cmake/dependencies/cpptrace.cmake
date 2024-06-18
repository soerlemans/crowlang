# Cpptrace (Stacktraces for C++)
message(STATUS "[+] Fetching cpptrace library.")

FetchContent_Declare(
  cpptrace
  GIT_REPOSITORY https://github.com/jeremy-rifkin/cpptrace.git
  GIT_TAG        v0.6.0
  GIT_PROGRESS TRUE
	SYSTEM
)

add_compile_definitions(CPPTRACE_UNWIND_WITH_UNWIND
  CPPTRACE_GET_SYMBOLS_WITH_LIBDWARF
)

FetchContent_MakeAvailable(cpptrace)

target_link_libraries(
	${TARGET_CROW_LIB}
	cpptrace::cpptrace
)

# On windows copy cpptrace.dll to the same directory as the executable for crow.
if(WIN32)
  add_custom_command(
    TARGET ${TARGET_CROW_LIB}
		POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:cpptrace> $<TARGET_FILE_DIR:${TARGET_CROW_LIB}>
  )
endif()
