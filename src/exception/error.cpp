#include "error.hpp"

// STL Includes:
#include <cassert>
#include <sstream>


namespace exception {
// Methods:
Error::Error(const std::string t_msg): std::exception{}, m_error{}
{
  std::stringstream ss;

  ss << t_msg;

#ifdef DEBUG
  ss << '\n';

	// TODO: Disable colors when --no-color is passed.
	// Print the stacktrace with colors.
  auto stacktrace{cpptrace::stacktrace::current()};
	stacktrace.print(ss, true);
#endif

  m_error = ss.str();
}

auto Error::what() const noexcept -> const char*
{
  return m_error.c_str();
}
} // namespace exception
