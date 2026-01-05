#ifndef CROW_CROW_AST_NODE_BUILTIN_TYPES_TYPE_NAME_HPP
#define CROW_CROW_AST_NODE_BUILTIN_TYPES_TYPE_NAME_HPP


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
class TypeName : public NodePosition, public Identifier {
  public:
  TypeName(TextPosition t_pos, std::string_view t_identifier);

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(TypeName, NodePosition)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~TypeName() = default;
};
} // namespace ast::node::user_types

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::user_types, TypeName);

#endif // CROW_CROW_AST_NODE_BUILTIN_TYPES_TYPE_NAME_HPP
