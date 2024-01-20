#ifndef CROW_AST_NODE_NODE_TRAITS_DECL_EXPR_HPP
#define CROW_AST_NODE_NODE_TRAITS_DECL_EXPR_HPP

// Includes:
#include "../node_interface.hpp"

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
  DeclExpr() = default;
  DeclExpr(TextPosition&& t_pos, std::string_view t_identifier,
           std::string_view t_type, NodePtr&& t_init);

  VISITABLE_PURE_ACCEPT(visitor::NodeVisitor);

  virtual ~DeclExpr() = default;
};
} // namespace ast::node::node_traits

#endif // CROW_AST_NODE_NODE_TRAITS_DECL_EXPR_HPP
