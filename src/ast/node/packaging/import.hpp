#ifndef CROW_AST_NODE_PACKAGING_IMPORT_HPP
#define CROW_AST_NODE_PACKAGING_IMPORT_HPP

// STL Includes:
#include <optional>
#include <string>
#include <vector>

// Includes:
#include "../node_interface.hpp"

// Local Includes:
#include "packaging.hpp"


namespace ast::node::packaging {
// Aliases:
using StrOpt = std::optional<std::string>;
using AliasPair = std::pair<std::string, StrOpt>;
using Imports = std::vector<AliasPair>;

// Classes:
class Import : public NodeInterface {
  private:
  Imports m_imports;

  public:
  Import() = default;

  auto add_import(std::string t_key) -> void;
  auto add_import(AliasPair t_pair) -> void;

  auto imports() const -> const Imports&;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Import() override = default;
};
} // namespace ast::node::packaging

#endif // CROW_AST_NODE_PACKAGING_IMPORT_HPP
