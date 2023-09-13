#include "function_call.hpp"


using namespace ast::node::functions;
using namespace ast::node::node_traits;

FunctionCall::FunctionCall(const std::string_view t_identifier,
                           NodeListPtr&& t_args)
  : Identifier{std::move(t_identifier)}, m_args{std::move(t_args)}
{}

auto FunctionCall::args() -> NodeListPtr&
{
  return m_args;
}
