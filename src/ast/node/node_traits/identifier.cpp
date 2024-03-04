#include "identifier.hpp"


namespace ast::node::node_traits {
// Methods:
Identifier::Identifier(std::string_view t_identifier)
  : m_identifier{t_identifier}
{}

auto Identifier::identifier() const -> std::string_view
{
  return m_identifier;
}
}
