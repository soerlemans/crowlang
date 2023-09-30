#include "type_error.hpp"


using namespace exception;

// TODO: Construct a more elaborate error message later
TypeError::TypeError(const std::string_view t_msg): m_error{t_msg}
{}

auto TypeError::what() const noexcept -> const char*
{
  return m_error.c_str();
}
