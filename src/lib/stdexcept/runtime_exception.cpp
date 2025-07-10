#include "runtime_exception.hpp"

namespace lib::stdexcept {
RuntimeException::RuntimeException(const std::string_view t_msg)
  : Exception{t_msg}
{}
} // namespace lib::stdexcept
