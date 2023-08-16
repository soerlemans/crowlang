#ifndef NEWLANG_DEBUG_LOG_HPP
#define NEWLANG_DEBUG_LOG_HPP

// STL Includes:
#include <iostream>
#include <string_view>

// Includes:
#include "../types.hpp"


// Only log if we are on the development build
#if DEBUG

// Macros:
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

namespace debug {
// Enums:
// Different logging levels
enum class LogLevel : u16 { CRITICAL = 0, ERROR, WARNING, INFO, VERBOSE };

#if DEBUG
// Macros:
// Stringify the given log leven in a case
#define LOG_CASE_STRINGIFY_LOGLEVEL(loglevel) \
  case LogLevel::loglevel:                    \
    return {#loglevel};

// Functions:
constexpr auto loglevel2str(const LogLevel t_loglevel) -> std::string_view
{
  switch(t_loglevel) {
    LOG_CASE_STRINGIFY_LOGLEVEL(CRITICAL);
    LOG_CASE_STRINGIFY_LOGLEVEL(ERROR);
    LOG_CASE_STRINGIFY_LOGLEVEL(WARNING);
    LOG_CASE_STRINGIFY_LOGLEVEL(INFO);
    LOG_CASE_STRINGIFY_LOGLEVEL(VERBOSE);

    default:
      // TODO: Error or handle unknown loglevel
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
