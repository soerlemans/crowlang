#ifndef INTERFACE_HPP
#define INTERFACE_HPP


// Includes:
#include "../node_interface.hpp"


namespace ast::node::typing {
class Interface : public NodeInterface {
  private:
  std::string m_identifier;
  NodeListPtr m_body;

  public:
  Interface(std::string t_identifier, NodeListPtr&& t_body);

  auto identifier() const -> std::string_view;
  auto body() -> NodeListPtr&;

  ~Interface() override = default;
};
} // namespace ast::node::typing

#endif // INTERFACE_HPP
