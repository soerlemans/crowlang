#include "diagnostic_error.hpp"

// Library Includes:
#include <cpptrace/cpptrace.hpp>

// STL Includes:
#include <cassert>
#include <sstream>

namespace diagnostic {
// Methods:
DiagnosticError::DiagnosticError(const std::string_view t_msg): m_error{}
{
  std::stringstream ss;

  // Set the given message.
  ss << t_msg;

#ifdef DEBUG
  ss << '\n';

  // TODO: Disable colors when --no-color is passed.
  // Print the stacktrace with colors.
  auto stacktrace{cpptrace::stacktrace::current()};
  stacktrace.print(ss, true);
#endif

  // Set the final error message string.
  m_error = ss.str();
}

auto DiagnosticError::what() const noexcept -> const std::string_view
{
  return m_error;
}
} // namespace diagnostic
