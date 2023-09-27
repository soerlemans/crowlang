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
  std::stringstream ss;

  t_os << rang::style::bold << rang::fg::red << "Test ";

  ss << loglevel2color(t_loglevel);
  ss << loglevel2str(t_loglevel);

  ss << rang::fg::reset;

  t_os << ss.str();


  return t_os;
}
} // namespace debug
