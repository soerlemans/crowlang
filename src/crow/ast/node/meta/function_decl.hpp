#ifndef CROW_CROW_AST_NODE_META_FUNCTION_DECL_HPP
#define CROW_CROW_AST_NODE_META_FUNCTION_DECL_HPP

// Relative Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"

namespace ast::node::meta {
// Using Statements:
using node_traits::Identifier;
using node_traits::Params;
using node_traits::TypeAnnotation;
using node_traits::TypeData;

// Classes:
class FunctionDecl : public Identifier,
                     public Params,
                     public TypeAnnotation,
                     public TypeData {
  public:
  FunctionDecl(std::string_view t_identifier, NodeListPtr&& t_params,
               std::string_view t_type);

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(FunctionDecl, Identifier, Params,
                                      TypeAnnotation)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~FunctionDecl() = default;
};
} // namespace ast::node::meta

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::meta, FunctionDecl);

#endif // CROW_CROW_AST_NODE_META_FUNCTION_DECL_HPP
