#ifndef CROW_AST_NODE_NODE_TRAITS_TYPE_HPP
#define CROW_AST_NODE_NODE_TRAITS_TYPE_HPP

// STL Includes:
#include <string_view>

// Includes:
#include "../node_interface.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::node_traits {
class TypeAnnotation : virtual public NodeInterface {
  protected:
  std::string m_type;

  public:
  TypeAnnotation(std::string_view t_type);

  virtual auto type() const -> std::string_view;

  VISITABLE_PURE_ACCEPT(visitor::NodeVisitor);

  ~TypeAnnotation() override = default;
};
} // namespace ast::node::node_traits

#endif // CROW_AST_NODE_NODE_TRAITS_TYPE_HPP
