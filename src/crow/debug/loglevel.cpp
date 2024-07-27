#include "loglevel.hpp"

// Absolute Includes:
#include "lib/enum2int.hpp"

// Internal:
namespace {
//! Private global keeping track of the current loglevel.
debug::LogLevel g_loglevel{debug::LogLevel::WARNING};
} // namespace

// Namespace Debug:
namespace debug {
[[nodiscard("Returned boolean result must be used.")]]
auto is_lower_loglevel(const LogLevel t_loglevel) -> bool
{
  using lib::enum2int;

  return enum2int(g_loglevel) >= enum2int(t_loglevel);
}

auto set_loglevel(const LogLevel t_loglevel) -> void
{
  g_loglevel = t_loglevel;
}
} // namespace debug

// Functions:
auto operator<<(std::ostream& t_os,
                const debug::LogLevel t_loglevel) -> std::ostream&
{
  using namespace rang;

  t_os << style::bold << loglevel2color(t_loglevel);
  t_os << debug::loglevel2str(t_loglevel);
  t_os << style::reset << fg::reset;

  return t_os;
}
