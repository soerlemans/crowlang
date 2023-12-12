#ifndef CROW_DEBUG_LOG_HPP
#define CROW_DEBUG_LOG_HPP

// STL Includes:
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string_view>

// Library Includes:
#include <rang.hpp>

// Includes:
#include "../container/source_position.hpp"
#include "../lib/types.hpp"

// Local Includes:
#include "log_macros.hpp"


namespace debug {
// Enums:
/*!
 * Enumeration of the different logging levels.
 * The lower log levels have the most severity.
 */
enum class LogLevel : u16 { CRITICAL = 0, ERROR, WARNING, INFO, VERBOSE };

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
// Macros:
//! Helper macro for converting @ref LogLevel to string representation.
#define DBG_CASE_LOGLEVEL2STR(loglevel) \
  case LogLevel::loglevel:              \
    return {#loglevel};

//! Helper macro for converting @ref LogLevel to rang foreground color.
#define DBG_CASE_LOGLEVEL2COLOR(loglevel, t_color) \
  case LogLevel::loglevel:                         \
    return rang::fg::t_color;

// Functions:
constexpr auto loglevel2str(const LogLevel t_loglevel) -> std::string_view
{
  switch(t_loglevel) {
    DBG_CASE_LOGLEVEL2STR(CRITICAL);
    DBG_CASE_LOGLEVEL2STR(ERROR);
    DBG_CASE_LOGLEVEL2STR(WARNING);
    DBG_CASE_LOGLEVEL2STR(INFO);
    DBG_CASE_LOGLEVEL2STR(VERBOSE);

    default:
      throw std::invalid_argument{
        "loglevel2str() could not convert loglevel to string"};
      break;
  }
}

constexpr auto loglevel2color(const LogLevel t_loglevel) -> rang::fg
{
  switch(t_loglevel) {
    DBG_CASE_LOGLEVEL2COLOR(CRITICAL, red);
    DBG_CASE_LOGLEVEL2COLOR(ERROR, red);
    DBG_CASE_LOGLEVEL2COLOR(WARNING, yellow);
    DBG_CASE_LOGLEVEL2COLOR(INFO, green);
    DBG_CASE_LOGLEVEL2COLOR(VERBOSE, cyan);

    default:
      throw std::invalid_argument{
        "loglevel2color() could not convert loglevel to string"};
      break;
  }
}

auto is_lower_loglevel(LogLevel t_loglevel) -> bool;
auto set_loglevel(LogLevel t_loglevel) -> void;

auto operator<<(std::ostream& t_os, LogLevel t_loglevel) -> std::ostream&;

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
