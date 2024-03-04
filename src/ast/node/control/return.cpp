#include "return.hpp"


namespace ast::node::control {
Return::Return(NodePtr&& t_expr): Expr{std::move(t_expr)}
{}
} // namespace ast::node::control
