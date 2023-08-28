#ifndef CROW_AST_NODE_OPERATORS_TERNARY_HPP
#define CROW_AST_NODE_OPERATORS_TERNARY_HPP

// Local Includes:
#include "binary_operator.hpp"
#include "operators.hpp"


namespace node::operators {
class Ternary : public NodeInterface {
  protected:
  NodePtr m_condition;
  NodePtr m_then;
  NodePtr m_alt;

  public:
  explicit Ternary(NodePtr&& t_condition, NodePtr&& t_then, NodePtr&& t_alt);

  auto condition() -> NodePtr&;
  auto then() -> NodePtr&;
  auto alt() -> NodePtr&;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Ternary() override = default;
};
} // namespace node::operators

#endif // CROW_AST_NODE_OPERATORS_TERNARY_HPP
