#ifndef CROW_AST_NODE_NODE_TRAITS_TYPING_TYPE_DATA_HPP
#define CROW_AST_NODE_NODE_TRAITS_TYPING_TYPE_DATA_HPP

// Includes:
#include "../../node_interface.hpp"

// Local Includes:
#include "types.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::node_traits::typing {
/*!
 * Class for annotating the AST with type information.
 * This information is then later used during code generation.
 */
class TypeData : virtual public NodeInterface {
  private:
  TypeVariant m_data;

  public:
  TypeData() = default;

  virtual auto set_type(TypeVariant t_data) -> void;
  virtual auto get_type() const -> const TypeVariant&;

  VISITABLE_PURE_ACCEPT(visitor::NodeVisitor);

  ~TypeData() override = default;
};
} // namespace ast::node::node_traits::typing

#endif // CROW_AST_NODE_NODE_TRAITS_TYPING_TYPE_DATA_HPP
