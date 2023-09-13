#include "function.hpp"


using namespace ast::node::functions;
using namespace ast::node::node_traits;

Function::Function(std::string_view t_identifier, NodeListPtr&& t_params,
                   NodeListPtr&& t_body)
  : Identifier{t_identifier},
    m_params{std::move(t_params)},
    m_body{std::move(t_body)}
{}

auto Function::params() -> NodeListPtr&
{
  return m_params;
}

auto Function::body() -> NodeListPtr&
{
  return m_body;
}
