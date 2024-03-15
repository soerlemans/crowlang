#include "args.hpp"

namespace ast::node::node_traits {
// Methods:
Args::Args(NodeListPtr&& t_args): m_args{std::move(t_args)}
{}

auto Args::args() -> NodeListPtr&
{
  return m_args;
}
} // namespace ast::node::node_traits
