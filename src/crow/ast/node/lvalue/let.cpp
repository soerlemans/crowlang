#include "let.hpp"

namespace ast::node::lvalue {
Let::Let(TextPosition t_pos, const std::string_view t_identifier,
         const std::string_view t_type, NodePtr&& t_init)
  : BindingExpr{std::move(t_pos), t_identifier, t_type, std::move(t_init)}
{}
} // namespace ast::node::lvalue
