#ifndef CROW_CROW_AST_NODE_TYPING_STRUCT_HPP
#define CROW_CROW_AST_NODE_TYPING_STRUCT_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"

namespace ast::node::user_types {
// Using Statements:
using node_traits::Body;
using node_traits::Identifier;
using node_traits::TypeData;

// Classes:
class Struct : public Identifier, public Body, public TypeData {
  public:
  Struct(std::string_view t_identifier, NodeListPtr&& t_body);

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(Struct, Identifier, Body)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Struct() = default;
};
} // namespace ast::node::user_types

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::user_types, Struct);

#endif // CROW_CROW_AST_NODE_TYPING_STRUCT_HPP
