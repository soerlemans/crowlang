#include "type_error.hpp"

// STL Includes:
#include <sstream>

// Local Includes:
#include "stacktrace_exception.hpp"


using namespace exception;

// Methods:
auto TypeError::format(std::string_view t_msg) -> std::string
{
  std::stringstream ss;

  ss << t_msg << "\n";

  return ss.str();
}

// TODO: Construct a more elaborate error message later
TypeError::TypeError(const std::string_view t_msg)
  : StacktraceException{format(t_msg)}
{}
