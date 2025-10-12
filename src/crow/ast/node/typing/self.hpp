#ifndef CROW_CROW_AST_NODE_TYPING_SELF_HPP
#define CROW_CROW_AST_NODE_TYPING_SELF_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"

namespace ast::node::typing {
// Aliases:
using node_traits::Identifier;
using node_traits::TypeAnnotation;
using node_traits::TypeData;

// Classes:
class Self : public Identifier, public TypeAnnotation, public TypeData {
  public:
  Self(std::string_view t_identifier, std::string_view t_type);

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(Self, Identifier, TypeAnnotation)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Self() = default;
};
} // namespace ast::node::typing

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::typing, Self);

#endif // CROW_CROW_AST_NODE_TYPING_SELF_HPP
