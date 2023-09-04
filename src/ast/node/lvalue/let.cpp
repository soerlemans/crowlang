#include "let.hpp"


using namespace ast::node::lvalue;

Let::Let(std::string_view t_identifier, NodePtr&& t_init)
  : m_identifier{std::move(t_identifier)}, m_init{std::move(t_init)}
{}

auto Let::identifier() const -> std::string_view
{
  return m_identifier;
}

auto Let::init() -> NodePtr&
{
  return m_init;
}
