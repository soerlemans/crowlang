#include "defer.hpp"


using namespace ast::node::control;

Defer::Defer(NodeListPtr&& t_body): m_body{std::move(t_body)}
{}

auto Defer::body() -> NodeListPtr&
{
  return m_body;
}
