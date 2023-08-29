#include "package.hpp"


using namespace ast::node::packaging;

Package::Package(std::string t_identifier)
  : m_identifier{std::move(t_identifier)}
{}

auto Package::identifier() const -> std::string_view
{
  return m_identifier;
}
