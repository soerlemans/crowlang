#include "defer.hpp"

namespace ast::node::control {
Defer::Defer(NodeListPtr&& t_body): Body{std::move(t_body)}
{}
} // namespace ast::node::control
