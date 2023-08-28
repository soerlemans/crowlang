#include "logical.hpp"


using namespace node::operators;

using namespace visitor;

// Not:
Not::Not(NodePtr&& t_left): UnaryOperator{std::forward<NodePtr>(t_left)}
{}


// And:
And::And(NodePtr&& t_left, NodePtr&& t_right)
  : BinaryOperator{std::forward<NodePtr>(t_left),
                   std::forward<NodePtr>(t_right)}
{}


// Or:
Or::Or(NodePtr&& t_left, NodePtr&& t_right)
  : BinaryOperator{std::forward<NodePtr>(t_left),
                   std::forward<NodePtr>(t_right)}
{}
