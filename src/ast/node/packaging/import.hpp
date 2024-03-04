#ifndef CROW_AST_NODE_PACKAGING_IMPORT_HPP
#define CROW_AST_NODE_PACKAGING_IMPORT_HPP

// STL Includes:
#include <optional>
#include <string>
#include <vector>

// Includes:
#include "../node_interface.hpp"

// Local Includes:
#include "fdecl.hpp"


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

  template<typename Archive>
  auto serialize(Archive& t_archive) -> void
  {
    t_archive(CEREAL_NVP(m_imports));
  }

  MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Import() = default;
};
} // namespace ast::node::packaging

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::packaging, Import);

#endif // CROW_AST_NODE_PACKAGING_IMPORT_HPP
