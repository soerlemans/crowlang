#include "init_expr.hpp"


using namespace ast::node::node_traits;

InitExpr::InitExpr(NodePtr&& t_init): m_init{std::move(t_init)}
{}

auto InitExpr::init_expr() -> NodePtr&
{
  return m_init;
}
