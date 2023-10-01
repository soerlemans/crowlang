#include "loop.hpp"


using namespace ast::node::control;
using namespace ast::node::node_traits;

Loop::Loop(NodePtr&& t_init, NodePtr&& t_condition, NodePtr&& t_expr,
           NodeListPtr&& t_body)
  : InitExpr{std::move(t_init)},
    Condition{std::move(t_condition)},
    Expr{std::move(t_expr)},
    Body{std::move(t_body)}

{}
