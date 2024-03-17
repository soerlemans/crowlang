#ifndef CROW_DEBUG_LOG_HPP
#define CROW_DEBUG_LOG_HPP

// STL Includes:
#include <iomanip>
#include <iostream>

// Includes:
#include "../container/source_position.hpp"

// Local Includes:
#include "log_macros.hpp"
#include "loglevel.hpp"

namespace debug {

// We use std::clog for logging
template<typename... Args>
auto print(Args&&... t_args) -> void
{
  // Fold expression
  (std::clog << ... << t_args);

  // Reset any rang modifiers
  std::clog << rang::style::reset;
  std::clog << rang::fg::reset << rang::bg::reset;
}

template<typename... Args>
auto println(Args&&... t_args) -> void
{
  // Fold expression
  print(std::forward<Args>(t_args)..., '\n');
}

// Logging faciltiies
#ifdef DEBUG
// Do not use this function with non primitive types it will not know how to
// Handle them and give an obscure tuple error
// TODO: Maybe inline log? We will be using it a lot for debugging
template<typename... Args>
inline auto log(const container::SourcePosition t_pos, LogLevel t_loglevel,
                Args&&... t_args) -> void
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

#endif // CROW_DEBUG_LOG_HPP
