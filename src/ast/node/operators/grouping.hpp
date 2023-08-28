#ifndef CROW_AST_NODE_OPERATORS_GROUPING_HPP
#define CROW_AST_NODE_OPERATORS_GROUPING_HPP

// Local Includes:
#include "operators.hpp"
#include "unary_operator.hpp"


namespace ast::node::operators {
class Grouping : public UnaryOperator {
  private:
  public:
  Grouping(NodePtr&& t_expr);

  auto expr() -> NodePtr;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Grouping() override = default;
};
} // namespace node::operators

#endif // CROW_AST_NODE_OPERATORS_GROUPING_HPP
