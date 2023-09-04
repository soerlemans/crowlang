#include "variable.hpp"


using namespace ast::node::lvalue;

Variable::Variable(std::string_view t_identifier)
  : m_identifier{std::move(t_identifier)}
{}

Variable::Variable(std::string_view t_identifier, std::string_view t_type)
  : m_identifier{t_identifier}, m_type{t_type}
{}

auto Variable::identifier() const -> std::string_view
{
  return m_identifier;
}

auto Variable::type() const -> std::string_view
{
  return m_type;
}
