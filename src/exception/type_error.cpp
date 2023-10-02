#include "type_error.hpp"

// Library Includes:
#include <cpptrace/cpptrace.hpp>

// STL Includes:
#include <sstream>

#include "../debug/log.hpp"


using namespace exception;

// TODO: Construct a more elaborate error message later
TypeError::TypeError(const std::string_view t_msg): m_error{}
{
  std::stringstream ss;

  // Throw exceptions if getting stacktraces fails somehow
  cpptrace::absorb_trace_exceptions(false);

  ss << t_msg << "\n";
  ss << cpptrace::stacktrace::current() << "\n";

  m_error = ss.str();
}

auto TypeError::what() const noexcept -> const char*
{
  return m_error.c_str();
}
