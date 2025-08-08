#ifndef CROW_CROW_AST_NODE_META_VAR_DECL_HPP
#define CROW_CROW_AST_NODE_META_VAR_DECL_HPP

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
class VarDecl : public Identifier,
                public TypeAnnotation,
                public TypeData,
                public AttributeData {
  public:
  VarDecl(std::string_view t_identifier, std::string_view t_type);

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(VarDecl, Identifier, TypeAnnotation)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~VarDecl() = default;
};
} // namespace ast::node::meta

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::meta, VarDecl);

#endif // CROW_CROW_AST_NODE_META_VAR_DECL_HPP
