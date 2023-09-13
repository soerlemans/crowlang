#ifndef CROW_AST_NODE_CONTROL_DEFER_HPP
#define CROW_AST_NODE_CONTROL_DEFER_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "control.hpp"


namespace ast::node::control {
// Aliases:
namespace nt = node_traits;

// Classes:
class Defer : public nt::Body {
  public:
  Defer(NodeListPtr&& t_body);

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Defer() override = default;
};
} // namespace ast::node::control

#endif // CROW_AST_NODE_CONTROL_DEFER_HPP
