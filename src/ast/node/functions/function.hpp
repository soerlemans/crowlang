#ifndef CROW_AST_NODE_FUNCTIONS_FUNCTION_HPP
#define CROW_AST_NODE_FUNCTIONS_FUNCTION_HPP

// Includes:
#include "../list.hpp"
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::functions {
// Aliases:
namespace nt = node_traits;

// Classes:
class Function : public nt::Identifier, public nt::Body {
  private:
  NodeListPtr m_params;

  public:
  Function(std::string_view t_identifier, NodeListPtr&& t_params,
           NodeListPtr&& t_body);

  auto params() -> NodeListPtr&;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Function() override = default;
};
} // namespace ast::node::functions

#endif // CROW_AST_NODE_FUNCTIONS_FUNCTION_HPP
