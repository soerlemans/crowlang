#ifndef CROW_AST_NODE_FUNCTIONS_FUNCTION_HPP
#define CROW_AST_NODE_FUNCTIONS_FUNCTION_HPP

#include "../list.hpp"
#include "../node_interface.hpp"

#include "functions.hpp"

namespace node::functions {
class Function : public NodeInterface {
  private:
  std::string m_identifier;
  NodeListPtr m_params;
  NodeListPtr m_body;

  public:
  Function(std::string t_identifier, NodeListPtr&& t_params, NodeListPtr&& t_body);

  auto identifier() const -> std::string_view;
  auto params() -> NodeListPtr&;
  auto body() -> NodeListPtr&;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Function() override = default;
};
} // namespace node::functions

#endif // CROW_AST_NODE_FUNCTIONS_FUNCTION_HPP
