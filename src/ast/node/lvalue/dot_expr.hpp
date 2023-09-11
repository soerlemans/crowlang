#ifndef DOT_EXPR_HPP
#define DOT_EXPR_HPP

// Includes:
#include "../node_interface.hpp"


namespace ast::node::lvalue {
class DotExpr : public NodeInterface {
  private:
  std::string m_identifier;
  NodePtr m_expr;

  public:
  DotExpr(std::string_view t_identifier, NodePtr&& t_init);

  auto identifier() const -> std::string_view;
  auto expr() -> NodePtr&;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~DotExpr() override = default;
};

} // namespace ast::node::lvalue

#endif // DOT_EXPR_HPP
