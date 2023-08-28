#include "function_call.hpp"


using namespace node::functions;

using namespace visitor;

FunctionCall::FunctionCall(std::string&& t_identifier, NodeListPtr&& t_args)
  : m_identifier{std::move(t_identifier)}, m_args{std::forward<NodeListPtr>(t_args)}
{}

auto FunctionCall::identifier() const -> std::string_view
{
  return {m_identifier};
}

auto FunctionCall::args() -> NodeListPtr&
{
  return m_args;
}

