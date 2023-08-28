#include "logical.hpp"


using namespace ast::node::operators;

// Not:
Not::Not(NodePtr&& t_left): UnaryOperator{std::move(t_left)}
{}


// And:
And::And(NodePtr&& t_left, NodePtr&& t_right)
  : BinaryOperator{std::move(t_left), std::move(t_right)}
{}


// Or:
Or::Or(NodePtr&& t_left, NodePtr&& t_right)
  : BinaryOperator{std::move(t_left), std::move(t_right)}
{}
