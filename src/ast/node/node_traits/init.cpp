#include "init.hpp"


using namespace ast::node::node_traits;

Init::Init(NodePtr&& t_init): m_init{std::move(t_init)}
{}

auto Init::init() -> NodePtr&
{
  return m_init;
}
