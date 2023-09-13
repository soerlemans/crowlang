#ifndef CROW_AST_NODE_TYPING_METHOD_DECL_HPP
#define CROW_AST_NODE_TYPING_METHOD_DECL_HPP


// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::typing {
// Aliases:
namespace nt = node_traits;

// Classes:
class MethodDecl : public nt::Identifier, public nt::TypeExpr {
  public:
  MethodDecl(std::string_view t_identifier, NodePtr&& t_type);

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~MethodDecl() override = default;
};
} // namespace ast::node::typing

#endif // CROW_AST_NODE_TYPING_METHOD_DECL_HPP
