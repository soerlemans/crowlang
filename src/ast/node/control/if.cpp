#include "if.hpp"


using namespace ast::node::control;
using namespace ast::node::node_traits;

If::If(NodePtr&& t_init, NodePtr&& t_condition, NodePtr&& t_then,
       NodePtr&& t_alt)
  : InitExpr{std::move(t_init)},
    Condition{std::move(t_condition)},
    Then{std::move(t_then)},
    Alt{std::move(t_alt)}
{}
