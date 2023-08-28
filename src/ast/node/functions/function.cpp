#include "function.hpp"


using namespace ast::node::functions;

Function::Function(std::string t_identifier, NodeListPtr&& t_params,
                   NodeListPtr&& t_body)
  : m_identifier{std::move(t_identifier)},
    m_params{std::move(t_params)},
    m_body{std::move(t_body)}
{}

auto Function::identifier() const -> std::string_view
{
  return {m_identifier};
}

auto Function::params() -> NodeListPtr&
{
  return m_params;
}

auto Function::body() -> NodeListPtr&
{
  return m_body;
}
