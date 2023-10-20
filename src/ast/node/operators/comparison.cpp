#include "comparison.hpp"


using namespace container;
using namespace ast::node::operators;
using namespace ast::node::node_traits;

Comparison::Comparison(TextPosition t_pos, ComparisonOp t_op, NodePtr&& t_left,
                       NodePtr&& t_right)
  : NodePosition{std::move(t_pos)},
    Op{t_op},
    BinaryOperator{std::move(t_left), std::move(t_right)}
{}
