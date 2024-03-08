#ifndef CROW_AST_NODE_TYPING_DOT_EXPR_HPP
#define CROW_AST_NODE_TYPING_DOT_EXPR_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::typing {
// Using Statements:
using node_traits::Expr;
using node_traits::Identifier;

// Classes:
class DotExpr : public Identifier, public Expr {
  public:
  DotExpr(std::string_view t_identifier, NodePtr&& t_init);

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(DotExpr, Identifier, Expr)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~DotExpr() = default;
};
} // namespace ast::node::typing

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::typing, DotExpr);

#endif // CROW_AST_NODE_TYPING_DOT_EXPR_HPP
