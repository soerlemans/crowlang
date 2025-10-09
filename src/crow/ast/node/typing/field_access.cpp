#include "field_access.hpp"

namespace ast::node::typing {
FieldAccess::FieldAccess(const std::string_view t_identifier, NodePtr&& t_expr)
  : Identifier{t_identifier}, Expr{std::move(t_expr)}
{}
} // namespace ast::node::typing
