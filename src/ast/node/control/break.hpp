#ifndef CROW_AST_NODE_CONTROL_BREAK_HPP
#define CROW_AST_NODE_CONTROL_BREAK_HPP

// Includes:
#include "../node_interface.hpp"

// Local Includes:
#include "control.hpp"


namespace ast::node::control {
class Break : public NodeInterface {
  public:
  MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Break() = default;
};
} // namespace node::control

#endif // CROW_AST_NODE_CONTROL_BREAK_HPP
