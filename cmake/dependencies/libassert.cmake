# Libassert (C++ assertion library):
message(STATUS "[+] Fetching libassert.")

FetchContent_Declare(
  libassert
  GIT_REPOSITORY https://github.com/jeremy-rifkin/libassert.git
  GIT_TAG        v2.0.2
  GIT_PROGRESS TRUE
	SYSTEM
)

FetchContent_MakeAvailable(libassert)

target_link_libraries(
	${TARGET_CROW_LIB}
	PUBLIC libassert::assert
)

# On windows copy libassert.dll to the same directory as the executable for crow.
if(WIN32)
  add_custom_command(
    TARGET ${TARGET_CROW_LIB}
		POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:libassert::assert>
    $<TARGET_FILE_DIR:${TARGET_CROW_LIB}>
  )
endif()
