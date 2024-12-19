#ifndef CROW_CROW_DEBUG_LOG_MACROS_HPP
#define CROW_CROW_DEBUG_LOG_MACROS_HPP

// Library Includes:
#include <boost/current_function.hpp>

// Absolute Includes:
#include "crow/container/source_position.hpp"
#include "crow/definitions.hpp"


// Macros:
#ifdef DEBUG
#define DBG_PRINTLN(...) debug::println(__VA_ARGS__)

//! Create a @ref SourcePosition of the line the macro is located on.
#define DBG_SOURCE_POS()                                         \
  container::SourcePosition                                      \
  {                                                              \
    CROW_PROJECT_RELATIVE_PATH, __LINE__, BOOST_CURRENT_FUNCTION \
  }

#define DBG_LOG(loglevel, ...) \
  debug::log(DBG_SOURCE_POS(), debug::LogLevel::loglevel, __VA_ARGS__)

#define DBG_SET_LOGLEVEL(loglevel) \
  debug::set_loglevel(debug::LogLevel::loglevel)

#else
// Stub the macros if we are not on the debugging build
#define DBG_PRINTLN(...) \
  do {                   \
  } while(0)

#define DBG_LOG(...) \
  do {               \
  } while(false)

#define DBG_SET_LOGLEVEL(level) \
  do {                          \
  } while(false)

#endif // DEBUG

// Utility macros for logging:
#define DBG_CRITICAL(...) DBG_LOG(CRITICAL, __VA_ARGS__)
#define DBG_ERROR(...)    DBG_LOG(ERROR, __VA_ARGS__)
#define DBG_WARNING(...)  DBG_LOG(WARNING, __VA_ARGS__)
#define DBG_NOTICE(...)   DBG_LOG(NOTICE, __VA_ARGS__)
#define DBG_INFO(...)     DBG_LOG(INFO, __VA_ARGS__)
#define DBG_VERBOSE(...)  DBG_LOG(VERBOSE, __VA_ARGS__)

#endif // CROW_CROW_DEBUG_LOG_MACROS_HPP
