#include "logical.hpp"


// Using Statements:
using namespace container;
using namespace ast::node::operators;
using namespace ast::node::node_traits;

// Not:
Not::Not(TextPosition t_pos, NodePtr&& t_left)
  : NodePosition{std::move(t_pos)}, UnaryOperator{std::move(t_left)}
{}


// And:
And::And(TextPosition t_pos, NodePtr&& t_left, NodePtr&& t_right)
  : NodePosition{std::move(t_pos)},
    BinaryOperator{std::move(t_left), std::move(t_right)}
{}


// Or:
Or::Or(TextPosition t_pos, NodePtr&& t_left, NodePtr&& t_right)
  : NodePosition{std::move(t_pos)},
    BinaryOperator{std::move(t_left), std::move(t_right)}
{}
