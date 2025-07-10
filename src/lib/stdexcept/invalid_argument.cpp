#include "invalid_argument.hpp"

namespace lib::stdexcept {
InvalidArgument::InvalidArgument(const std::string_view t_msg): Exception{t_msg}
{}
} // namespace lib::stdexcept
