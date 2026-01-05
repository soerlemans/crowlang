#ifndef CROW_CROW_AST_NODE_BUILTIN_TYPES_POINTER_HPP
#define CROW_CROW_AST_NODE_BUILTIN_TYPES_POINTER_HPP


// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"

namespace ast::node::user_types {
// Aliases:
using container::TextPosition;
using node_traits::Identifier;
using node_traits::NodePosition;
using node_traits::TypeData;

// Classes:
class Pointer : public NodePosition {
  public:
  Pointer(TextPosition t_pos);

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(Pointer, NodePosition)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Pointer() = default;
};
} // namespace ast::node::user_types

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::user_types, Pointer);

#endif // CROW_CROW_AST_NODE_BUILTIN_TYPES_POINTER_HPP
