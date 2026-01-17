#ifndef ACRIS_ACRIS_AST_NODE_CONTROL_CONTINUE_HPP
#define ACRIS_ACRIS_AST_NODE_CONTROL_CONTINUE_HPP

// Includes
#include "../node_interface.hpp"

// Local Includes:
#include "fdecl.hpp"

namespace ast::node::control {
class Continue : public NodeInterface {
  public:
  Continue() = default;

  AST_ARCHIVE_DEFINE_SERIALIZE_METHOD_NIL()
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Continue() = default;
};
} // namespace ast::node::control

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::control, Continue);

#endif // ACRIS_ACRIS_AST_NODE_CONTROL_CONTINUE_HPP
