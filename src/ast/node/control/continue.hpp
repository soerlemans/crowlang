#ifndef CROW_AST_NODE_CONTROL_CONTINUE_HPP
#define CROW_AST_NODE_CONTROL_CONTINUE_HPP

// Includes
#include "../node_interface.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::control {
class Continue : public NodeInterface {
  public:
  // MAKE_ARCHIVEABLE(Continue)
  // {}

  MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Continue() = default;
};
} // namespace node::control

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::control, Continue);

#endif // CROW_AST_NODE_CONTROL_CONTINUE_HPP
