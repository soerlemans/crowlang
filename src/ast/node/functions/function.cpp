#include "function.hpp"


using namespace ast::node::functions;
using namespace ast::node::node_traits;

Function::Function(const std::string_view t_identifier, NodeListPtr&& t_params,
                   NodeListPtr&& t_body)
  : Identifier{t_identifier},
    Body{std::move(t_body)},
    m_params{std::move(t_params)}
{}

auto Function::params() -> NodeListPtr&
{
  return m_params;
}
