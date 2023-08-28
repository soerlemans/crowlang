#ifndef CROW_AST_NODE_OPERATORS_INCREMENT_HPP
#define CROW_AST_NODE_OPERATORS_INCREMENT_HPP

// Local Includes:
#include "operators.hpp"
#include "unary_operator.hpp"


namespace ast::node::operators {
class Increment : public UnaryOperator {
  private:
  bool m_prefix;

  public:
  Increment(NodePtr&& t_left, bool t_prefix);

  auto prefix() const -> bool;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Increment() override = default;
};
} // namespace node::operators

#endif
