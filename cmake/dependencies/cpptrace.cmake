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

FetchContent_MakeAvailable(cpptrace)

target_link_libraries(
	${PROJECT_NAME}
	cpptrace
)
