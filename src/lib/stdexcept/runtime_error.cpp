#include "runtime_error.hpp"

namespace lib::stdexcept {
RuntimeError::RuntimeError(const std::string_view t_msg): Exception{t_msg}
{}
} // namespace lib::stdexcept
