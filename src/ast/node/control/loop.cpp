#include "loop.hpp"


using namespace ast::node::control;

Loop::Loop(NodePtr&& t_init, NodePtr&& t_condition, NodePtr&& t_expr,
           NodeListPtr&& t_body)
  : m_init{std::move(t_init)},
    m_condition{std::move(t_condition)},
    m_expr{std::move(t_expr)},
    m_body{std::move(t_body)}
{}

auto Loop::init() -> NodePtr&
{
  return m_init;
}

auto Loop::condition() -> NodePtr&
{
  return m_condition;
}

auto Loop::expr() -> NodePtr&
{
  return m_expr;
}

auto Loop::body() -> NodeListPtr&
{
  return m_body;
}
