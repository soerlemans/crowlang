#ifndef CROW_AST_NODE_PACKAGING_IMPORT_HPP
#define CROW_AST_NODE_PACKAGING_IMPORT_HPP

// STL Includes:
#include <optional>
#include <string>

// Includes:
#include "../map.hpp"

// Local Includes:
#include "packaging.hpp"


namespace ast::node::packaging {
// Aliases:
using StrOpt = std::optional<std::string>;
using AliasPair = std::pair<std::string, StrOpt>;
using Imports = Map<std::string, StrOpt>;

// Classes:
class Import : public NodeInterface {
  private:
  std::string m_identifier;
  Imports m_imports;

  public:
  Import(std::string t_identifier);

  auto add_import(std::string t_key) -> void;
  auto add_import(AliasPair t_pair) -> void;

  auto identifier() const -> std::string_view;
  auto imports() const -> const Imports&;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Import() override = default;
};
} // namespace ast::node::packaging

#endif // CROW_AST_NODE_PACKAGING_IMPORT_HPP
