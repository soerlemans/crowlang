#ifndef STRUCT_HPP
#define STRUCT_HPP

// Includes:
#include "../node_interface.hpp"


namespace ast::node::typing {
class Struct : public NodeInterface {
  private:
  std::string m_identifier;
  NodeListPtr m_body;

  public:
  Struct(std::string t_identifier, NodeListPtr&& t_body);

  auto identifier() const -> std::string_view;
  auto body() -> NodeListPtr&;

  ~Struct() override = default;
};
} // namespace ast::node::typing

#endif // STRUCT_HPP
