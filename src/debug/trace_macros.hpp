#ifndef CROW_DEBUG_TRACE_MACROS_HPP
#define CROW_DEBUG_TRACE_MACROS_HPP

// Includes:
#include "../macros.hpp"


#if DEBUG
#define DBG_TRACE_INIT() int m_counter{0};

// TRACE is intended for showing which functions call which in a tree like
// manner
#define DBG_TRACE(loglevel, ...)                      \
  debug::Trace CONCAT(trace, __COUNTER__)             \
  {                                                   \
    m_counter, debug::LogLevel::loglevel, __VA_ARGS__ \
  }

// Creates a trace object in an enclosed scope, usefull for printing TRACE info
// on the same level within a function
#define DBG_TRACE_PRINT(loglevel, ...)                    \
  do {                                                    \
    debug::Trace CONCAT(trace, __COUNTER__){              \
      m_counter, debug::LogLevel::loglevel, __VA_ARGS__}; \
  } while(false)

#else
// Stub the macros if we are not on the debugging build:
#define DBG_TRACE_INIT()

#define DBG_TRACE(loglevel, ...) \
  do {                           \
  } while(false)

#define DBG_TRACE_PRINT(loglevel, ...) \
  do {                                 \
  } while(false)

#endif // DEBUG
#endif // CROW_DEBUG_TRACE_MACROS_HPP
