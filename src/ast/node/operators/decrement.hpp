#ifndef CROW_AST_NODE_OPERATORS_DECREMENT_HPP
#define CROW_AST_NODE_OPERATORS_DECREMENT_HPP

// Local Includes:
#include "operators.hpp"
#include "unary_operator.hpp"


namespace ast::node::operators {
class Decrement : public UnaryOperator {
  private:
  bool m_prefix;

  public:
  Decrement(NodePtr&& t_left, bool t_prefix);

  auto prefix() const -> bool;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Decrement() override = default;
};
} // namespace node::operators

#endif // CROW_AST_NODE_OPERATORS_DECREMENT_HPP
