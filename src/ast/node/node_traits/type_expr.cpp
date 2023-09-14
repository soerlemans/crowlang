#include "type_expr.hpp"


using namespace ast::node::node_traits;

TypeExpr::TypeExpr(NodePtr&& t_type): m_type{std::move(t_type)}
{}

auto TypeExpr::type() -> NodePtr&
{
  return m_type;
}
