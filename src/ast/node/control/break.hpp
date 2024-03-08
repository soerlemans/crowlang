#ifndef CROW_AST_NODE_CONTROL_BREAK_HPP
#define CROW_AST_NODE_CONTROL_BREAK_HPP

// Includes:
#include "../node_interface.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::control {
class Break : public NodeInterface {
  public:
  Break() = default;

  AST_ARCHIVE_DEFINE_SERIALIZE_METHOD_NIL()
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Break() = default;
};
} // namespace ast::node::control

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::control, Break);

#endif // CROW_AST_NODE_CONTROL_BREAK_HPP
