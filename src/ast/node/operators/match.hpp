#ifndef CROW_AST_NODE_OPERATORS_MATCH_HPP
#define CROW_AST_NODE_OPERATORS_MATCH_HPP

#include "binary_operator.hpp"
#include "operators.hpp"


namespace node::operators {
enum class MatchOp { MATCH, NO_MATCH };

// EreMatch:
class Match : public BinaryOperator {
  private:
  MatchOp m_op;

  public:
  Match(MatchOp t_op, NodePtr&& t_string, NodePtr&& t_pattern);

	auto op() const -> MatchOp;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Match() override = default;
};
} // namespace node::operators

#endif // CROW_AST_NODE_OPERATORS_MATCH_HPP
