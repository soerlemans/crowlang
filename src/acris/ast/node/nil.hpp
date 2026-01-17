#ifndef ACRIS_ACRIS_AST_NODE_NIL_HPP
#define ACRIS_ACRIS_AST_NODE_NIL_HPP

// Local Includes:
#include "fdecl.hpp"
#include "node_interface.hpp"

namespace ast::node {
class Nil : public NodeInterface {
  public:
  AST_ARCHIVE_DEFINE_SERIALIZE_METHOD_NIL()
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Nil() = default;
};
} // namespace ast::node

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node, Nil);

#endif // ACRIS_ACRIS_AST_NODE_NIL_HPP
