#ifndef NEWLANG_DEBUG_LOG_HPP
#define NEWLANG_DEBUG_LOG_HPP

// STL Includes:
#include <stdexcept>
#include <iostream>
#include <string_view>

// Includes:
#include "../types.hpp"

// Local Includes:
#include "log_macros.hpp"


namespace debug {
// Enums:
//! Specify the different LogLevel's
enum class LogLevel : u16 { CRITICAL = 0, ERROR, WARNING, INFO, VERBOSE };

// Logging faciltiies
#if DEBUG
// Macros:
//! Helper macro for converting LogLevel enum val to string representation
#define DBG_CASE_STRINGIFY_LOGLEVEL(loglevel) \
  case LogLevel::loglevel:                    \
    return {#loglevel};

// Functions:
constexpr auto loglevel2str(const LogLevel t_loglevel) -> std::string_view
{
  switch(t_loglevel) {
    DBG_CASE_STRINGIFY_LOGLEVEL(CRITICAL);
    DBG_CASE_STRINGIFY_LOGLEVEL(ERROR);
    DBG_CASE_STRINGIFY_LOGLEVEL(WARNING);
    DBG_CASE_STRINGIFY_LOGLEVEL(INFO);
    DBG_CASE_STRINGIFY_LOGLEVEL(VERBOSE);

    default:
			throw std::invalinvalid_argument{""}:
      break;
  }

  return {"NONE"};
}

auto is_lower_loglevel(LogLevel t_loglevel) -> bool;
auto set_loglevel(LogLevel t_loglevel) -> void;

// We use std::clog for logging
template<typename... Args>
auto print(Args&&... t_args) -> void
{
  // Fold expression
  (std::clog << ... << t_args);
}

template<typename... Args>
auto println(Args&&... t_args) -> void
{
  // Fold expression
  print(std::forward<Args>(t_args)..., '\n');
}

// Do not use this function with non primitive types it will not know how to
// Handle them and give an obscure tuple error
// TODO: Maybe inline log? We will be using it a lot for debugging
template<typename... Args>
auto log(std::string_view t_file, std::string_view t_function, int t_lineno,
         LogLevel t_loglevel, Args&&... t_args) -> void
{
  // Ignore higher log levels
  if(is_lower_loglevel(t_loglevel)) {
    // Denote loglevel
    print('[', loglevel2str(t_loglevel), ']');

    // Module information
    print('[', t_file, ':', t_lineno, " -> ", t_function, "()] => ");

    // Log what we want to log
    println(std::forward<Args>(t_args)...);
  }
}

#endif // DEBUG
} // namespace debug

#endif // NEWLANG_DEBUG_LOG_HPP
