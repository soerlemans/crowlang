#ifndef NEWLANG_DEBUG_TRACE_HPP
#define NEWLANG_DEBUG_TRACE_HPP

// STL Includes:
#include <string>

// Local Includes:
#include "log.hpp"


// Only facilitate Trace if we are on the DEBUG build
#if DEBUG

// Helper macros for TRACE:
#define CONCAT(a, b)       CONCAT_INNER(a, b)
#define CONCAT_INNER(a, b) a##b

#define DBG_TRACE_INIT() int m_counter{0};

// TRACE is intended for showing which functions call which in a tree like
// manner
#define DBG_TRACE(loglevel, ...)                      \
  Trace CONCAT(trace, __COUNTER__)                    \
  {                                                   \
    m_counter, debug::LogLevel::loglevel, __VA_ARGS__ \
  }


// Creates a trace object in an enclosed scope, usefull for printing TRACE info
// on the same level within a function
#define DBG_TRACE_PRINT(loglevel, ...)                                     \
  do {                                                                     \
    Trace CONCAT(trace, __COUNTER__){m_counter, debug::LogLevel::loglevel, \
                                     __VA_ARGS__};                         \
  } while(false)

// Trace class used for figuring out
class Trace {
  private:
  // Counter that denotes the indentation level
  int &m_counter;

  // Denotes if the message should be printed?
  bool m_print;

  public:
  template<typename... Args>
  Trace(int &t_counter, debug::LogLevel t_loglevel, Args &&...t_args)
    : m_counter{t_counter}, m_print{debug::is_lower_loglevel(t_loglevel)}
  {
    if(m_print) {
      DBG_PRINTLN(indent_text(), std::forward<Args>(t_args)..., " - (",
                  m_counter, ')');

      m_counter++;
    }
  }

  auto indent_text() -> std::string;

  virtual ~Trace();
};

#else

// Stub the macros if we are not on the debugging build
#define DBG_TRACE_INIT()
#define DBG_TRACE(loglevel, ...) \
  do {                           \
  } while(false)

#define DBG_TRACE_PRINT(loglevel, ...) \
  do {                                 \
  } while(false)

#endif // DEBUG
#endif // NEWLANG_DEBUG_TRACE_HPP
