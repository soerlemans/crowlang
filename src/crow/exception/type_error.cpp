#include "type_error.hpp"

namespace exception {
// Methods:
auto TypeError::format(std::string_view t_msg) -> std::string
{
  std::stringstream ss;

  ss << t_msg << '\n';

  return ss.str();
}

// TODO: Construct a more elaborate error message later
TypeError::TypeError(const std::string_view t_msg): Error{format(t_msg)}
{}
} // namespace exception
