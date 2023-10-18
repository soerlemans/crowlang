#include "logical.hpp"


using namespace ast::node::operators;
using namespace ast::node::node_traits;

// Not:
Not::Not(ct::TextPosition t_pos, NodePtr&& t_left)
  : NodePosition{std::move(t_pos)}, UnaryOperator{std::move(t_left)}
{}


// And:
And::And(NodePtr&& t_left, NodePtr&& t_right)
  : BinaryOperator{std::move(t_left), std::move(t_right)}
{}


// Or:
Or::Or(NodePtr&& t_left, NodePtr&& t_right)
  : BinaryOperator{std::move(t_left), std::move(t_right)}
{}
