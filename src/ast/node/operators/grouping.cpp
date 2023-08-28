#include "grouping.hpp"


using namespace ast::node::operators;

Grouping::Grouping(NodePtr&& t_expr)
  : UnaryOperator{std::move(t_expr)}
{}
