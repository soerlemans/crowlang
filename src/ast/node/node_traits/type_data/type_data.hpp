#ifndef CROW_AST_NODE_NODE_TRAITS_TYPE_DATA_TYPE_DATA_HPP
#define CROW_AST_NODE_NODE_TRAITS_TYPE_DATA_TYPE_DATA_HPP

// Includes:
#include "../../node_interface.hpp"

// Local Includes:
#include "type_variant.hpp"

// Local Includes:
// #include "fdecl.hpp"


namespace ast::node::node_traits::type_data {
class TypeData : virtual public NodeInterface {
  private:
  // TypeVariant m_data;

  public:
  TypeData() = default;

  // virtual auto set_data(const TypeVariant) -> void;
  // virtual auto get_data() const -> const TypeVariant&;

  VISITABLE_PURE_ACCEPT(visitor::NodeVisitor);

  ~TypeData() override = default;
};
} // namespace ast::node::node_traits::type_data

#endif // CROW_AST_NODE_NODE_TRAITS_TYPE_DATA_TYPE_DATA_HPP
