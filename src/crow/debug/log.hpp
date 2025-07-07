#ifndef CROW_CROW_DEBUG_LOG_HPP
#define CROW_CROW_DEBUG_LOG_HPP

// STL Includes:
#include <iomanip>
#include <iostream>

// Absolute Includes:
#include "crow/container/source_position.hpp"

// Local Includes:
#include "log_macros.hpp"
#include "loglevel.hpp"

namespace debug {
// Using declarations:
using container::SourcePosition;

// Functions:
template<typename... Args>
inline auto print(Args &&...t_args) -> void
{
  // We use std::clog for logging.
  (std::clog << ... << t_args);

  // Reset any rang modifiers.
  std::clog << rang::style::reset;
  std::clog << rang::fg::reset << rang::bg::reset;
}

template<typename... Args>
inline auto println(Args &&...t_args) -> void
{
  print(std::forward<Args>(t_args)..., '\n');
}

// Logging faciltiies
#ifdef DEBUG
/*!
 * @brief Used to log the compiler.
 *
 * @param[in] t_pos  Position in source code where the log call is made from.
 * @param[in] t_pos  The @ref LogLevel to log to.
 * @param[in] t_args Arguments to log.
 */
template<typename... Args>
inline auto log(SourcePosition &&t_pos, LogLevel t_loglevel, Args &&...t_args)
  -> void
{
  using namespace rang;

  // Ignore higher log levels
  if(is_lower_loglevel(t_loglevel)) {
    // Denote loglevel
    print('[', t_loglevel, ']');

    // Module information
    print('[', t_pos, "]: ");

    // Log what we want to log
    println(std::forward<Args>(t_args)...);
  }
}
#endif // DEBUG
} // namespace debug

#endif // CROW_CROW_DEBUG_LOG_HPP
