#include "let.hpp"


using namespace ast::node::lvalue;

Let::Let(const std::string& t_identifier, NodePtr&& t_init)
  : m_identifier{std::move(t_identifier)}, m_init{std::move(t_init)}
{}

auto Let::identifier() const -> const std::string&
{
  return m_identifier;
}


auto Let::init() -> NodePtr&
{
  return m_init;
}
