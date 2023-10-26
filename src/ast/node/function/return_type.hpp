#ifndef CROW_AST_NODE_FUNCTION_RETURN_TYPE_HPP
#define CROW_AST_NODE_FUNCTION_RETURN_TYPE_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::function {
// Aliases:
namespace nt = node_traits;

// Classes:
class ReturnType : public nt::Type {
  public:
  ReturnType(std::string_view t_type);

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~ReturnType() override = default;
};
} // namespace ast::node::functions

#endif // CROW_AST_NODE_FUNCTION_RETURN_TYPE_HPP
