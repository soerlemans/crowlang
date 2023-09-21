#include "const.hpp"


using namespace ast::node::lvalue;
using namespace ast::node::node_traits;

Const::Const(const std::string_view t_identifier, NodePtr&& t_init)
  : Identifier{t_identifier}, m_init{std::move(t_init)}
{}

auto Const::init() -> NodePtr&
{
  return m_init;
}



