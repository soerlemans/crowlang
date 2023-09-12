#include "struct.hpp"


using namespace ast::node::typing;


Struct::Struct(std::string t_identifier, NodeListPtr&& t_body)
  : m_identifier{std::move(t_identifier)}, m_body{std::move(t_body)}
{}

auto Struct::identifier() const -> std::string_view
{
  return {m_identifier};
}

auto Struct::body() -> NodeListPtr&
{
  return m_body;
}
