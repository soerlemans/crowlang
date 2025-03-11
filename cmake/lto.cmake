# Only enable link time optimization.
if(CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
include(CheckIPOSupported)
check_ipo_supported(RESULT supported OUTPUT error)

if( supported )
  message(STATUS "Enabling IPO/LTO.")

  set_property(
    TARGET ${TARGET_CROW_LIB}
    PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE
  )

  set_property(
    TARGET ${TARGET_CROW_BIN}
    PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE
  )
else()
    message(STATUS "IPO / LTO not supported: <${error}>")
endif()
endif()
