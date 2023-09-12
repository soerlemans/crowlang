#include "interface.hpp"


using namespace ast::node::typing;

Interface::Interface(std::string t_identifier, NodeListPtr&& t_body)
  : m_identifier{std::move(t_identifier)}, m_body{std::move(t_body)}
{}

auto Interface::identifier() const -> std::string_view
{
  return {m_identifier};
}

auto Interface::body() -> NodeListPtr&
{
  return m_body;
}


