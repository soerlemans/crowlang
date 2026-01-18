#include "todo.hpp"

namespace lib::stdexcept {
Todo::Todo(const std::string_view t_msg): Exception{t_msg}
{}
} // namespace lib::stdexcept
