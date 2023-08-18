#ifndef CROW_DEBUG_LOG_MACROS_HPP
#define CROW_DEBUG_LOG_MACROS_HPP


// Macros:
#if DEBUG
#define DBG_PRINTLN(...) debug::println(__VA_ARGS__)

#define DBG_LOG(loglevel, ...)                                        \
  debug::log(__FILE__, __func__, __LINE__, debug::LogLevel::loglevel, \
             __VA_ARGS__)

#define DBG_SET_LOGLEVEL(loglevel) \
  debug::set_loglevel(debug::LogLevel::loglevel)

#else
// Stub the macros if we are not on the debugging build
#define DBG_PRINTLN(...) \
  do {                   \
  } while(0)

#define DBG_LOG(...) \
  do {               \
  } while(0)

#define DBG_SET_LOGLEVEL(level) \
  do {                          \
  } while(0)

#endif // DEBUG

// Utility macros for logging:
#define DBG_CRITICAL(...) DBG_LOG(CRITICAL, __VA_ARGS__)
#define DBG_ERROR(...)    DBG_LOG(ERROR, __VA_ARGS__)
#define DBG_WARNING(...)  DBG_LOG(WARNING, __VA_ARGS__)
#define DBG_INFO(...)     DBG_LOG(INFO, __VA_ARGS__)
#define DBG_VERBOSE(...)  DBG_LOG(VERBOSE, __VA_ARGS__)

#endif // CROW_DEBUG_LOG_MACROS_HPP
