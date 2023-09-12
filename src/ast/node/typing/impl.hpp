#ifndef IMPL_HPP
#define IMPL_HPP

// Includes:
#include "../node_interface.hpp"


namespace ast::node::typing {
class Impl : public NodeInterface {
  private:
  std::string m_identifier;
  NodeListPtr m_body;

  public:
  Impl(std::string t_identifier, NodeListPtr&& t_body);

  auto identifier() const -> std::string_view;
  auto body() -> NodeListPtr&;

  ~Impl() override = default;
};
} // namespace ast::node::typing

#endif // IMPL_HPP
