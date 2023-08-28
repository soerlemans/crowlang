#include "if.hpp"

#include <utility>


using namespace node::control;

using namespace visitor;

If ::If(NodePtr&& t_condition, NodePtr&& t_then)
  : m_condition{std::forward<NodePtr>(t_condition)},
    m_then{std::forward<NodePtr>(t_then)}
{}


If::If(NodePtr&& t_condition, NodePtr&& t_then, NodePtr&& t_alt)
  : m_condition{std::forward<NodePtr>(t_condition)},
    m_then{std::forward<NodePtr>(t_then)},
    m_alt{std::forward<NodePtr>(t_alt)}
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

