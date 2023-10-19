#ifndef CROW_AST_NODE_NODE_TRAITS_DECL_EXPR_HPP
#define CROW_AST_NODE_NODE_TRAITS_DECL_EXPR_HPP

// Includes:
#include "../node_interface.hpp"

// Local Includes:
#include "fdecl.hpp"
#include "identifier.hpp"
#include "init_expr.hpp"
#include "node_position.hpp"
#include "type.hpp"


namespace ast::node::node_traits {
// Aliases:
namespace ct = container;

// Classes:
class DeclExpr : public NodePosition,
                 public Identifier,
                 public Type,
                 public InitExpr {
  public:
  DeclExpr(ct::TextPosition&& t_pos, std::string_view t_identifier,
           std::string_view t_str, NodePtr&& t_init);

  VISITABLE_PURE_ACCEPT(visitor::NodeVisitor);

  ~DeclExpr() override = default;
};
} // namespace ast::node::node_traits

#endif // CROW_AST_NODE_NODE_TRAITS_DECL_EXPR_HPP
