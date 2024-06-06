#ifndef CROW_CROW_DEBUG_LOGLEVEL_HPP
#define CROW_CROW_DEBUG_LOGLEVEL_HPP

// STL Includes:
#include <stdexcept>
#include <string_view>

// Library Includes:
#include <rang.hpp>

// Absolute Includes:
#include "lib/types.hpp"

// Macros:
//! Helper macro for converting @ref LogLevel to string representation.
#define DBG_CASE_LOGLEVEL2STR(loglevel) \
  case LogLevel::loglevel:              \
    return {#loglevel};

//! Helper macro for converting @ref LogLevel to rang foreground color.
#define DBG_CASE_LOGLEVEL2COLOR(loglevel, t_color) \
  case LogLevel::loglevel:                         \
    return rang::fg::t_color;

namespace debug {
// Enums:
/*!
 * Enumeration of the different logging levels.
 * The lower log levels have the most severity.
 */
enum class LogLevel : u16 {
  CRITICAL = 0,
  ERROR,
  WARNING,
  INFO,
  VERBOSE
};

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
} // namespace debug

// Functions:
auto operator<<(std::ostream& t_os, debug::LogLevel t_loglevel)
  -> std::ostream&;

#endif // CROW_CROW_DEBUG_LOGLEVEL_HPP
