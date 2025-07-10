#include "unexpected_nullptr.hpp"

namespace lib::stdexcept {
UnexpectedNullptr::UnexpectedNullptr(const std::string_view t_msg): Exception{t_msg}
{}
} // namespace lib::stdexcept
