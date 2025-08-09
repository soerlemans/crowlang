#include "logic_error.hpp"

namespace lib::stdexcept {
LogicError::LogicError(const std::string_view t_msg): Exception{t_msg}
{}
} // namespace lib::stdexcept
