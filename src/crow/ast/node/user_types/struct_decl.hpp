#ifndef CROW_CROW_AST_NODE_USER_TYPES_STRUCT_DECL_HPP
#define CROW_CROW_AST_NODE_USER_TYPES_STRUCT_DECL_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"

namespace ast::node::user_types {
// Using Statements:
using node_traits::Identifier;

// Classes:
class StructDecl : public Identifier {
  public:
  StructDecl(std::string_view t_identifier);

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(StructDecl, Identifier)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~StructDecl() = default;
};
} // namespace ast::node::user_types

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::user_types, StructDecl);

#endif // CROW_CROW_AST_NODE_USER_TYPES_STRUCT_DECL_HPP
