#ifndef CROW_AST_NODE_TYPING_METHOD_DECL_HPP
#define CROW_AST_NODE_TYPING_METHOD_DECL_HPP


// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"
#include <string_view>

namespace ast::node::typing {
// Using Statements:
using node_traits::Identifier;
using node_traits::Params;
using node_traits::TypeAnnotation;

// Classes:
class MethodDecl : public Identifier, public Params, public TypeAnnotation {
  public:
  MethodDecl(std::string_view t_identifier, NodeListPtr&& t_params,
             std::string_view t_type);

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(MethodDecl, Identifier, TypeAnnotation)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~MethodDecl() = default;
};
} // namespace ast::node::typing

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::typing, MethodDecl);

#endif // CROW_AST_NODE_TYPING_METHOD_DECL_HPP
