#ifndef CROW_AST_NODE_FUNCTION_FUNCTION_HPP
#define CROW_AST_NODE_FUNCTION_FUNCTION_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::function {
// Aliases:
namespace nt = node_traits;

// Classes:
class Function : public nt::Identifier,
                 public nt::Params,
                 public nt::Type,
                 public nt::Body {
  public:
  Function(std::string_view t_identifier, NodeListPtr&& t_params,
           std::string_view t_type, NodeListPtr&& t_body);

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Function() override = default;
};
} // namespace ast::node::functions

#endif // CROW_AST_NODE_FUNCTION_FUNCTION_HPP
