#include "log.hpp"


using namespace debug;

namespace {
// Private variables:
LogLevel g_loglevel{LogLevel::WARNING};
} // namespace

namespace debug {
// Public functions:
// This function checks if the LogLevel is lower than the current g_loglevel
// t_loglevel is used in macros use [[maybe_unused]] to silence warnings
// TOOD: This could be constexpr
[[nodiscard]] auto is_lower_loglevel(const LogLevel t_loglevel) -> bool
{
  return enum2int(g_loglevel) >= enum2int(t_loglevel);
}

auto set_loglevel(const LogLevel t_loglevel) -> void
{
  g_loglevel = t_loglevel;
}

auto operator<<(std::ostream& t_os, const LogLevel t_loglevel) -> std::ostream&
{
  using namespace rang;

  t_os << style::bold << loglevel2color(t_loglevel);
  t_os << loglevel2str(t_loglevel);
  t_os << style::reset << fg::reset;

  return t_os;
}
} // namespace debug
