#include "init_expr.hpp"


namespace ast::node::node_traits {
// Methods:
InitExpr::InitExpr(NodePtr&& t_init): m_init{std::move(t_init)}
{}

auto InitExpr::init_expr() -> NodePtr&
{
  return m_init;
}
} // namespace ast::node::node_traits
