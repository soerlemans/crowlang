#ifndef CROW_AST_NODE_PACKAGING_MODULE_DECL_HPP
#define CROW_AST_NODE_PACKAGING_MODULE_DECL_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::packaging {
// Using Statements:
using node_traits::Identifier;

// Classes:
class ModuleDecl : public Identifier {
  public:
  ModuleDecl(std::string_view t_identifier);

  MAKE_TRAITS_ARCHIVEABLE(ModuleDecl, Identifier)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~ModuleDecl() = default;
};
} // namespace ast::node::packaging

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::packaging, ModuleDecl);

#endif // CROW_AST_NODE_PACKAGING_MODULE_DECL_HPP
