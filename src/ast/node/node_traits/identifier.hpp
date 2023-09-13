#ifndef CROW_AST_NODE_NODE_TRAITS_IDENTIFIER_HPP
#define CROW_AST_NODE_NODE_TRAITS_IDENTIFIER_HPP

// STL Includes:
#include <string_view>

// Includes:
#include "../node_interface.hpp"


namespace ast::node::node_traits {
class Identifier : public NodeInterface {
  protected:
  std::string m_identifier;

  public:
  Identifier(std::string_view t_identifier);

  virtual auto identifier() const -> std::string_view;

  auto accept(visitor::NodeVisitor* t_visitor) -> void override = 0;

  ~Identifier() override = default;
};
} // namespace ast::node::node_traits

#endif // CROW_AST_NODE_NODE_TRAITS_IDENTIFIER_HPP
