#ifndef CROW_AST_NODE_CONTROL_RETURN_HPP
#define CROW_AST_NODE_CONTROL_RETURN_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::control {
// Aliases:
namespace nt = node_traits;

// Classes:
class Return : public nt::Expr {
  public:
  Return(NodePtr&& t_expr);

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Return() override = default;
};
} // namespace ast::node::control

#endif // CROW_AST_NODE_CONTROL_RETURN_HPP
