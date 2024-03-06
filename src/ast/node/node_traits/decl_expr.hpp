#ifndef CROW_AST_NODE_NODE_TRAITS_DECL_EXPR_HPP
#define CROW_AST_NODE_NODE_TRAITS_DECL_EXPR_HPP

// Includes:
#include "../include.hpp"

// Local Includes:
#include "fdecl.hpp"
#include "identifier.hpp"
#include "init_expr.hpp"
#include "node_position.hpp"
#include "type_annotation.hpp"


namespace ast::node::node_traits {
// Using Statements:
using container::TextPosition;

// Classes:
class DeclExpr : public NodePosition,
                 public Identifier,
                 public TypeAnnotation,
                 public InitExpr {
  public:
  DeclExpr(TextPosition&& t_pos, std::string_view t_identifier,
           std::string_view t_type, NodePtr&& t_init);

  MAKE_TRAITS_ARCHIVEABLE(DeclExpr, NodePosition, Identifier, TypeAnnotation,
                          InitExpr)
  VISITABLE_PURE_ACCEPT(visitor::NodeVisitor);

  virtual ~DeclExpr() = default;
};
} // namespace ast::node::node_traits

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::node_traits, DeclExpr);

#endif // CROW_AST_NODE_NODE_TRAITS_DECL_EXPR_HPP
