#include "stdexcept.hpp"

// Library Includes:
#include <cpptrace/cpptrace.hpp>

namespace lib::stdexcept {
Exception::Exception(const std::string_view t_msg): m_msg{}
{
  std::stringstream ss;

  // Set the given message.
  ss << t_msg << '\n';

  // TODO: Disable colors when --no-color is passed.
  // Print the stacktrace with colors.
  auto stacktrace{cpptrace::stacktrace::current()};
  stacktrace.print(ss, true);

  // Set the final error message string.
  m_msg = ss.str();
}

auto Exception::what() const noexcept -> const std::string_view
{
  return m_msg;
}
} // namespace lib::stdexcept
