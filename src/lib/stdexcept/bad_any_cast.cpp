#include "bad_any_cast.hpp"

namespace lib::stdexcept {
BadAnyCast::BadAnyCast(const std::string_view t_msg): Exception{t_msg}
{}
} // namespace lib::stdexcept
