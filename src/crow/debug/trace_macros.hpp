#ifndef CROW_CROW_DEBUG_TRACE_MACROS_HPP
#define CROW_CROW_DEBUG_TRACE_MACROS_HPP

// Absolute Includes:
#include "lib/macros.hpp"


// Macros:
#ifdef DEBUG
#define DBG_TRACE_INIT() int m_counter__{0}

// TRACE is intended for showing which functions call which in a tree like
// manner
#define DBG_TRACE(loglevel, ...)                      \
  debug::Trace CONCAT(trace, __COUNTER__)             \
  {                                                   \
    m_counter__, debug::LogLevel::loglevel, __VA_ARGS__ \
  }

// Creates a trace object in an enclosed scope, usefull for printing TRACE info
// on the same level within a function
#define DBG_TRACE_PRINT(loglevel, ...)                    \
  do {                                                    \
    debug::Trace CONCAT(trace, __COUNTER__){              \
      m_counter__, debug::LogLevel::loglevel, __VA_ARGS__}; \
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

#define DBG_TRACE_FN(t_loglevel) DBG_TRACE(t_loglevel, __func__)

#endif // CROW_CROW_DEBUG_TRACE_MACROS_HPP
