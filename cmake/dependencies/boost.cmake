# Boost (C++ utility libraries):
message(STATUS "[+] Finding Boost library.")

find_package(
  Boost
  1.83
  COMPONENTS program_options filesystem iostreams thread
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
