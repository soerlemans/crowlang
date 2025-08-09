#ifndef CROW_CROW_AST_NODE_META_LET_DECL_HPP
#define CROW_CROW_AST_NODE_META_LET_DECL_HPP

// Relative Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"

namespace ast::node::meta {
// Using Statements:
using node_traits::AttributeData;
using node_traits::Identifier;
using node_traits::TypeAnnotation;
using node_traits::TypeData;

// Classes:
class LetDecl : public Identifier,
                public TypeAnnotation,
                public TypeData,
                public AttributeData {
  public:
  LetDecl(std::string_view t_identifier, std::string_view t_type);

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(LetDecl, Identifier, TypeAnnotation)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~LetDecl() = default;
};
} // namespace ast::node::meta

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::meta, LetDecl);

#endif // CROW_CROW_AST_NODE_META_LET_DECL_HPP
