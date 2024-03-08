#ifndef CROW_AST_NODE_TYPING_STRUCT_HPP
#define CROW_AST_NODE_TYPING_STRUCT_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::typing {
// Using Statements:
using node_traits::Body;
using node_traits::Identifier;

// Classes:
class Struct : public Identifier, public Body {

  public:
  Struct(std::string_view t_identifier, NodeListPtr&& t_body);

  MAKE_TRAITS_ARCHIVEABLE(Struct, Identifier, Body)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Struct() = default;
};
} // namespace ast::node::typing

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::typing, Struct);

#endif // CROW_AST_NODE_TYPING_STRUCT_HPP
