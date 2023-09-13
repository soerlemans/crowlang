#ifndef CROW_AST_NODE_FUNCTIONS_FUNCTION_CALL_HPP
#define CROW_AST_NODE_FUNCTIONS_FUNCTION_CALL_HPP

// STL Includes:
#include <string>
#include <string_view>

// Includes:
#include "../list.hpp"
#include "../node_interface.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::functions {
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
} // namespace ast::node::functions

#endif // CROW_AST_NODE_FUNCTIONS_FUNCTION_CALL_HPP
