#ifndef CROW_CROW_AST_NODE_TYPING_SELF_HPP
#define CROW_CROW_AST_NODE_TYPING_SELF_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"

namespace ast::node::user_types {
// Aliases:
using node_traits::TypeData;

// Classes:
class Self : public TypeData {
  public:
  Self();

  AST_ARCHIVE_DEFINE_SERIALIZE_METHOD_NIL()
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Self() = default;
};
} // namespace ast::node::user_types

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::user_types, Self);

#endif // CROW_CROW_AST_NODE_TYPING_SELF_HPP
