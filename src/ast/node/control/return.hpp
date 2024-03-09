#ifndef CROW_AST_NODE_CONTROL_RETURN_HPP
#define CROW_AST_NODE_CONTROL_RETURN_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"

namespace ast::node::control {
// Using Statements:
using node_traits::Expr;

// Classes:
class Return : public Expr {
  public:
  Return(NodePtr&& t_expr);

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(Return, Expr)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Return() = default;
};
} // namespace ast::node::control

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::control, Return);

#endif // CROW_AST_NODE_CONTROL_RETURN_HPP
