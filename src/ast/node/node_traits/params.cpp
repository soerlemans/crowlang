#include "params.hpp"


namespace ast::node::node_traits {
// Methods:
Params::Params(NodeListPtr&& t_params): m_params{std::move(t_params)}
{}

auto Params::params() -> NodeListPtr&
{
  return m_params;
}
} // namespace ast::node::node_traits
