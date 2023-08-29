#include "import.hpp"


using namespace ast::node::packaging;

Import::Import(std::string t_identifier): m_identifier{std::move(t_identifier)}
{}


auto Import::add_import(std::string t_key) -> void
{
  m_imports.insert({std::move(t_key), StrOpt{}});
}

auto Import::add_import(AliasPair t_pair) -> void
{
  m_imports.insert(std::move(t_pair));
}


auto Import::identifier() const -> std::string_view
{
  return m_identifier;
}

auto Import::imports() const -> const Imports&
{
  return m_imports;
}
