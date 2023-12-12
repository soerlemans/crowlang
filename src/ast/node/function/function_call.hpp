#ifndef CROW_AST_NODE_FUNCTION_FUNCTION_CALL_HPP
#define CROW_AST_NODE_FUNCTION_FUNCTION_CALL_HPP

// Includes:
#include "../list.hpp"
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::function {
// Aliases:
namespace nt = node_traits;

// Classes:
class FunctionCall : public nt::Identifier {
  private:
  std::string m_identifier;
  NodeListPtr m_args;

  public:
  FunctionCall(std::string_view t_identifier, NodeListPtr&& t_args);

  auto args() -> NodeListPtr&;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~FunctionCall() override = default;
};
} // namespace ast::node::functions

#endif // CROW_AST_NODE_FUNCTION_FUNCTION_CALL_HPP
