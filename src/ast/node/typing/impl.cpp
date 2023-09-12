#include "impl.hpp"


using namespace ast::node::typing;

Impl::Impl(std::string t_identifier, NodeListPtr&& t_body)
  : m_identifier{std::move(t_identifier)}, m_body{std::move(t_body)}
{}

auto Impl::identifier() const -> std::string_view
{
  return {m_identifier};
}

auto Impl::body() -> NodeListPtr&
{
  return m_body;
}
