#include "binding_expr.hpp"

namespace ast::node::node_traits {
// Methods:
BindingExpr::BindingExpr(TextPosition&& t_pos,
                         const std::string_view t_identifier, NodePtr&& t_type,
                         NodePtr&& t_init)
  : NodePosition{std::move(t_pos)},
    Identifier{t_identifier},
    TypeAnnotation{std::move(t_type)},
    TypeData{},
    InitExpr{std::move(t_init)}
{}
} // namespace ast::node::node_traits
