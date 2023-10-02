#include "stacktrace_exception.hpp"

// STL Includes:
#include <cassert>
#include <sstream>


using namespace exception;

// Methods:
StacktraceException::StacktraceException(const std::string t_msg)
  : STACKTRACE_EXCEPTION_PARENT{}, m_error{}
{
	std::stringstream ss;

	ss << t_msg;

#ifdef DEBUG
  // TODO: Relocate somewhere else to only be called once
  cpptrace::absorb_trace_exceptions(false);

	ss << "\n";

  // Print the trace to the stream without colors (they mess up the output).
  ss << STACKTRACE_EXCEPTION_PARENT::what() << '\n';
#endif

  m_error = ss.str();
}

auto StacktraceException::what() const noexcept -> const char*
{
  return m_error.c_str();
}
