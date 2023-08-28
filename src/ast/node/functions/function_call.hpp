#ifndef CROW_AST_NODE_FUNCTIONS_FUNCTION_CALL_HPP
#define CROW_AST_NODE_FUNCTIONS_FUNCTION_CALL_HPP

// STL Includes:
#include <string>
#include <string_view>

#include "../list.hpp"
#include "../node_interface.hpp"

#include "functions.hpp"


namespace node::functions {
class FunctionCall : public NodeInterface {
  private:
  std::string m_identifier;
  NodeListPtr m_args;

  public:
  FunctionCall(std::string&& t_identifier, NodeListPtr&& t_args);

  auto identifier() const -> std::string_view;
  auto args() -> NodeListPtr&;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~FunctionCall() override = default;
};
} // namespace node::functions

#endif // CROW_AST_NODE_FUNCTIONS_FUNCTION_CALL_HPP
