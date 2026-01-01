# Boost (C++ utility libraries):
message(STATUS "[+] Finding Boost library.")

#FetchContent_Declare(
#    Boost
#    GIT_REPOSITORY https://github.com/boostorg/boost.git
#    GIT_TAG boost-1.89.0
#)
#
#FetchContent_MakeAvailable(Boost)

find_package(
  Boost
  1.89
  COMPONENTS system program_options filesystem iostreams thread
  REQUIRED
)

include_directories(
  SYSTEM
  ${Boost_INCLUDE_DIRS}
)

target_link_libraries(
  ${TARGET_CROW_LIB}
  PUBLIC ${Boost_LIBRARIES}
)
