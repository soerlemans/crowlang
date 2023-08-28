#include "comparison.hpp"


using namespace node::operators;

using namespace visitor;

Comparison::Comparison(ComparisonOp t_op, NodePtr&& t_lhs, NodePtr&& t_rhs)
  : BinaryOperator{std::forward<NodePtr>(t_lhs), std::forward<NodePtr>(t_rhs)},
    m_op{t_op}
{}

auto Comparison::op() const -> ComparisonOp
{
  return m_op;
}
