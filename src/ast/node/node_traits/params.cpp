#include "params.hpp"


using namespace ast::node::node_traits;

Params::Params(NodeListPtr&& t_params): m_params{std::move(t_params)}
{}

auto Params::params() -> NodeListPtr&
{
  return m_params;
}
