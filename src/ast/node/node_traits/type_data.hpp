#ifndef CROW_AST_NODE_NODE_TRAITS_TYPE_DATA_HPP
#define CROW_AST_NODE_NODE_TRAITS_TYPE_DATA_HPP

// Includes:
#include "../node_interface.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::node_traits {
class TypeData : virtual public NodeInterface {
  // check::SymbolData m_data;

  public:
  TypeData() = default;

  // virtual auto set_data(const SymbolData) -> void;
  // virtual auto get_data() const -> check::SymbolData;

  VISITABLE_PURE_ACCEPT(visitor::NodeVisitor);

  ~TypeData() override = default;
};
} // namespace ast::node::node_traits

#endif // CROW_AST_NODE_NODE_TRAITS_TYPE_DATA_HPP
