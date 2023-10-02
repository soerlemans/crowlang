#include "stacktrace_exception.hpp"

// STL Includes:
#include <sstream>


using namespace exception;

StackTraceException::StacktraceException(std::string_view t_msg)
  : STACKTRACE_EXCEPTION_PARENT{}, m_error{}
{
  std::stringstream ss;

  ss << t_msg;

#ifdef DEBUG
  // Get resolved stack trace
  ss << get_what();
#endif

  m_error = ss.str();
}

auto StackTraceException::what() const noexcept -> const char*
{
  return m_error.c_str();
}
