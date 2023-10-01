#include "type_error.hpp"

// Library Includes:
#include <boost/stacktrace.hpp>

// STL Includes:
#include <sstream>

#include "../debug/log.hpp"


using namespace exception;

// TODO: Construct a more elaborate error message later
TypeError::TypeError(const std::string_view t_msg): m_error{}
{
  std::stringstream ss;

  ss << t_msg << "\n";
  ss << boost::stacktrace::stacktrace() << "\n";

  m_error = ss.str();
}

auto TypeError::what() const noexcept -> const char*
{
  return m_error.c_str();
}
