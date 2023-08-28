#include "variable.hpp"


using namespace node::lvalue;

using namespace visitor;

Variable::Variable(const std::string& t_identifier)
  : m_identifier{std::move(t_identifier)}
{}

auto Variable::identifier() const -> const std::string&
{
  return m_identifier;
}
