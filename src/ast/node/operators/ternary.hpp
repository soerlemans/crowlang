#ifndef CROW_AST_NODE_OPERATORS_TERNARY_HPP
#define CROW_AST_NODE_OPERATORS_TERNARY_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "binary_operator.hpp"
#include "fdecl.hpp"


namespace ast::node::operators {
// Aliases:
namespace nt = node_traits;

// Classes:
class Ternary : public nt::Condition {
  protected:
  NodePtr m_then;
  NodePtr m_alt;

  public:
  explicit Ternary(NodePtr&& t_condition, NodePtr&& t_then, NodePtr&& t_alt);

  auto then() -> NodePtr&;
  auto alt() -> NodePtr&;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Ternary() override = default;
};
} // namespace ast::node::operators

#endif // CROW_AST_NODE_OPERATORS_TERNARY_HPP
