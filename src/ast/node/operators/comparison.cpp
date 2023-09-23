#include "comparison.hpp"


using namespace ast::node::operators;
using namespace ast::node::node_traits;

Comparison::Comparison(ComparisonOp t_op, NodePtr&& t_lhs, NodePtr&& t_rhs)
  : BinaryOperator{std::move(t_lhs), std::move(t_rhs)}, m_op{t_op}
{}

auto Comparison::op() const -> ComparisonOp
{
  return m_op;
}
