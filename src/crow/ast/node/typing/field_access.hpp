#ifndef CROW_CROW_AST_NODE_TYPING_DOT_EXPR_HPP
#define CROW_CROW_AST_NODE_TYPING_DOT_EXPR_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"

namespace ast::node::typing {
// Using Statements:
using node_traits::Expr;
using node_traits::Identifier;

// Classes:
class FieldAccess : public Identifier, public Expr {
  public:
  FieldAccess(std::string_view t_identifier, NodePtr&& t_init);

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(FieldAccess, Identifier, Expr)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~FieldAccess() = default;
};
} // namespace ast::node::typing

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::typing, FieldAccess);

#endif // CROW_CROW_AST_NODE_TYPING_DOT_EXPR_HPP
