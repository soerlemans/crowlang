#include "ternary.hpp"

// STL Includes:
#include <utility>


using namespace ast::node::operators;

Ternary::Ternary(NodePtr&& t_condition, NodePtr&& t_then, NodePtr&& t_alt)
  : m_condition{std::move(t_condition)},
    m_then{std::move(t_then)},
    m_alt{std::move(t_alt)}
{}

auto Ternary::condition() -> NodePtr&
{
  return m_condition;
}

auto Ternary::then() -> NodePtr&
{
  return m_then;
}

auto Ternary::alt() -> NodePtr&
{
  return m_alt;
}
