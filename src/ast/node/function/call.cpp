#include "call.hpp"


namespace ast::node::function {
Call::Call(const std::string_view t_identifier, NodeListPtr&& t_args)
  : Identifier{std::move(t_identifier)}, m_args{std::move(t_args)}
{}

auto Call::args() -> NodeListPtr&
{
  return m_args;
}
} // namespace ast::node::function
