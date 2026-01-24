set(ACRIS_STDLIB_PLATFORM "${CMAKE_SYSTEM_NAME}" CACHE STRING "Target platform.")
string(TOLOWER "${ACRIS_STDLIB_PLATFORM}" LOCAL_PLATFORM)

message(STATUS "Platform: ${LOCAL_PLATFORM}")

# Check platform.
if(LOCAL_PLATFORM STREQUAL "linux")
elseif(LOCAL_PLATFORM STREQUAL "openbsd")
elseif(LOCAL_PLATFORM STREQUAL "darwin")
elseif(LOCAL_PLATFORM STREQUAL "windows")
elseif(LOCAL_PLATFORM STREQUAL "bare_metal")
else()
  message(FATAL_ERROR "Platform ${LOCAL_PLATFORM} unknown!")
endif()

set(PLATFORM_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${LOCAL_PLATFORM}")
if(NOT EXISTS "${PLATFORM_DIR}")
    message(FATAL_ERROR "Platform ${LOCAL_PLATFORM} is not supported.")
endif()

add_subdirectory("${LOCAL_PLATFORM}")
