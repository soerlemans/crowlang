#include "match.hpp"


using namespace node::operators;

using namespace visitor;

Match::Match(MatchOp t_op, NodePtr&& t_string, NodePtr&& t_pattern)
  : BinaryOperator{std::forward<NodePtr>(t_string),
                   std::forward<NodePtr>(t_pattern)},
    m_op{t_op}
{}

auto Match::op() const -> MatchOp
{
  return m_op;
}
