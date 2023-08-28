#include "if.hpp"


using namespace ast::node::control;

If ::If(NodePtr&& t_condition, NodePtr&& t_then)
  : m_condition{std::move(t_condition)}, m_then{std::move(t_then)}
{}


If::If(NodePtr&& t_condition, NodePtr&& t_then, NodePtr&& t_alt)
  : m_condition{std::move(t_condition)},
    m_then{std::move(t_then)},
    m_alt{std::move(t_alt)}
{}

auto If::condition() -> NodePtr&
{
  return m_condition;
}

auto If::then() -> NodePtr&
{
  return m_then;
}

auto If::alt() -> NodePtr&
{
  return m_alt;
}
