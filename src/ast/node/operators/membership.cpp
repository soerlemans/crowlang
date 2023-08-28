#include "membership.hpp"


using namespace node::operators;

using namespace visitor;

Membership::Membership(NodePtr&& t_lhs, std::string&& t_name)
  : UnaryOperator{std::forward<NodePtr>(t_lhs)},
    m_name{std::forward<std::string>(t_name)}
{}

auto Membership::name() const -> std::string_view
{
  return {m_name};
}
