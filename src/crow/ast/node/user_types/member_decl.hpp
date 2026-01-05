#ifndef CROW_CROW_AST_NODE_TYPING_MEMBER_DECL_HPP
#define CROW_CROW_AST_NODE_TYPING_MEMBER_DECL_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"

namespace ast::node::user_types {
// Using Statements:
using node_traits::Identifier;
using node_traits::TypeAnnotation;
using node_traits::TypeData;

// Classes:
class MemberDecl : public Identifier, public TypeAnnotation, public TypeData {
  public:
  MemberDecl(std::string_view t_identifier, std::string_view t_type);

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(MemberDecl, Identifier, TypeAnnotation)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~MemberDecl() = default;
};
} // namespace ast::node::user_types

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::user_types, MemberDecl);

#endif // CROW_CROW_AST_NODE_TYPING_MEMBER_DECL_HPP
