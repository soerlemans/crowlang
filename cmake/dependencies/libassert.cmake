# Catch2 (C++ Unit testing framework):
message(STATUS "[+] Fetching libassert.")

FetchContent_Declare(
  libassert
  GIT_REPOSITORY https://github.com/jeremy-rifkin/libassert.git
  GIT_TAG        v2.0.2
)

FetchContent_MakeAvailable(libassert)

target_link_libraries(your_target libassert::assert)

# On windows copy libassert.dll to the same directory as the executable for crow.
if(WIN32)
  add_custom_command(
    TARGET your_target POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:libassert::assert>
    $<TARGET_FILE_DIR:your_target>
  )
endif()
