#ifndef CROW_CROW_DEBUG_LOGLEVEL_HPP
#define CROW_CROW_DEBUG_LOGLEVEL_HPP

// STL Includes:
#include <stdexcept>
#include <string_view>

// Library Includes:
#include <rang.hpp>

// Absolute Includes:
#include "lib/stdtypes.hpp"

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
 *
 * - Critical: Sanity check logging, if this is shown something goes very wrong.
 * - Error: General errors that should terminate.
 * - Warning: General warnings (non terminating).
 * - Notice: Important information that should always be shown.
 * - Info: Informative information useful for when debugging.
 * - Verbose: Execution details, used for rigorous debugging.
 */
enum class LogLevel : u16 {
  CRITICAL = 0,
  ERROR,
  WARNING,
  NOTICE,
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
    DBG_CASE_LOGLEVEL2STR(NOTICE);
    DBG_CASE_LOGLEVEL2STR(INFO);
    DBG_CASE_LOGLEVEL2STR(VERBOSE);

    default:
      throw std::invalid_argument{
        "loglevel2str() could not convert loglevel to string."};
      break;
  }

  return {};
}

constexpr auto loglevel2color(const LogLevel t_loglevel) -> rang::fg
{
  switch(t_loglevel) {
    DBG_CASE_LOGLEVEL2COLOR(CRITICAL, red);
    DBG_CASE_LOGLEVEL2COLOR(ERROR, red);
    DBG_CASE_LOGLEVEL2COLOR(WARNING, yellow);
    DBG_CASE_LOGLEVEL2COLOR(NOTICE, blue);
    DBG_CASE_LOGLEVEL2COLOR(INFO, green);
    DBG_CASE_LOGLEVEL2COLOR(VERBOSE, cyan);

    default:
      throw std::invalid_argument{
        "loglevel2color() could not convert loglevel to string."};
      break;
  }
}

/*!
 * Checks if the @ref LogLevel is lower than the current g_loglevel.
 */
auto is_lower_loglevel(LogLevel t_loglevel) -> bool;


/*!
 * Change the loglevel of the logging.
 */
auto set_loglevel(LogLevel t_loglevel) -> void;
} // namespace debug

// Functions:
auto operator<<(std::ostream& t_os, debug::LogLevel t_loglevel)
  -> std::ostream&;

#endif // CROW_CROW_DEBUG_LOGLEVEL_HPP
