#include "decl_expr.hpp"

namespace ast::node::node_traits {
// Methods:
DeclExpr::DeclExpr(TextPosition&& t_pos, const std::string_view t_identifier,
                   const std::string_view t_type, NodePtr&& t_init)
  : NodePosition{std::move(t_pos)},
    Identifier{t_identifier},
    TypeAnnotation{t_type},
    InitExpr{std::move(t_init)}
{}
} // namespace ast::node::node_traits
