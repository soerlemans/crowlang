#include "unexpected_monostate.hpp"

namespace lib::stdexcept {
UnexpectedMonostate::UnexpectedMonostate(const std::string_view t_msg)
  : Exception{t_msg}
{}
} // namespace lib::stdexcept
