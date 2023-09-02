#include "if.hpp"


using namespace ast::node::control;

If::If(NodePtr&& t_init, NodePtr&& t_condition, NodeListPtr&& t_then,
       NodeListPtr&& t_alt)
  : m_init{std::move(t_init)},
    m_condition{std::move(t_condition)},
    m_then{std::move(t_then)},
    m_alt{std::move(t_alt)}
{}

auto If::init() -> NodePtr&
{
  return m_init;
}

auto If::condition() -> NodePtr&
{
  return m_condition;
}

auto If::then() -> NodeListPtr&
{
  return m_then;
}

auto If::alt() -> NodeListPtr&
{
  return m_alt;
}
