#include "loop.hpp"


using namespace ast::node::control;
using namespace ast::node::node_traits;

Loop::Loop(ct::TextPosition t_pos, NodePtr&& t_init, NodePtr&& t_condition,
           NodePtr&& t_expr, NodeListPtr&& t_body)
  : NodePosition{std::move(t_pos)},
    InitExpr{std::move(t_init)},
    Condition{std::move(t_condition)},
    Expr{std::move(t_expr)},
    Body{std::move(t_body)}

{}
