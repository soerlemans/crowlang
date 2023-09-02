#include "import.hpp"


using namespace ast::node::packaging;

auto Import::add_import(std::string t_key) -> void
{
  m_imports.emplace_back(std::move(t_key), StrOpt{});
}

auto Import::add_import(AliasPair t_pair) -> void
{
  m_imports.push_back(std::move(t_pair));
}

auto Import::imports() const -> const Imports&
{
  return m_imports;
}
