#ifndef CROW_DEBUG_TRACE_HPP
#define CROW_DEBUG_TRACE_HPP

// STL Includes:
#include <string>

// Local Includes:
#include "log.hpp"
#include "trace_macros.hpp"


// Only facilitate Trace if we are on the DEBUG build
#if DEBUG
namespace debug {
/*! Trace class is used for printing nested structures using a lifetime
 *!
 */
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
} // namespace debug

#endif // DEBUG
#endif // CROW_DEBUG_TRACE_HPP
