#ifndef CROW_AST_NODE_TYPING_METHOD_DECL_HPP
#define CROW_AST_NODE_TYPING_METHOD_DECL_HPP


// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"
#include <string_view>


namespace ast::node::typing {
// Aliases:
namespace nt = node_traits;

// Classes:
class MethodDecl : public nt::Identifier,
                   public nt::Params,
                   public nt::TypeAnnotation {
  public:
  MethodDecl(std::string_view t_identifier, NodeListPtr&& t_params,
             std::string_view t_type);

  MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~MethodDecl() = default;
};
} // namespace ast::node::typing

#endif // CROW_AST_NODE_TYPING_METHOD_DECL_HPP
