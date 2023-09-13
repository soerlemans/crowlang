#ifndef CROW_AST_NODE_TYPING_DOT_EXPR_HPP
#define CROW_AST_NODE_TYPING_DOT_EXPR_HPP

// Includes:
#include "../node_traits/include.hpp"


namespace ast::node::lvalue {
// Aliases:
namespace nt = node_traits;

// Classes:
class DotExpr : public nt::Identifier {
  private:
  NodePtr m_expr;

  public:
  DotExpr(std::string_view t_identifier, NodePtr&& t_init);

  auto expr() -> NodePtr&;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~DotExpr() override = default;
};

} // namespace ast::node::lvalue

#endif // CROW_AST_NODE_TYPING_DOT_EXPR_HPP
