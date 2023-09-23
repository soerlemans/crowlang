#ifndef CROW_AST_NODE_PACKAGING_MODULE_DECL_HPP
#define CROW_AST_NODE_PACKAGING_MODULE_DECL_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::packaging {
// Aliases:
namespace nt = node_traits;

// Classes:
class ModuleDecl : public nt::Identifier {
  public:
  ModuleDecl(std::string_view t_identifier);

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~ModuleDecl() override = default;
};
} // namespace ast::node::packaging

#endif // CROW_AST_NODE_PACKAGING_MODULE_DECL_HPP
