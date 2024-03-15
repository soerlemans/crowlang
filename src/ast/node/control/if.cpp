#include "if.hpp"

namespace ast::node::control {
If::If(TextPosition t_pos, NodePtr&& t_init, NodePtr&& t_condition,
       NodePtr&& t_then, NodePtr&& t_alt)
  : NodePosition{std::move(t_pos)},
    InitExpr{std::move(t_init)},
    Condition{std::move(t_condition)},
    Then{std::move(t_then)},
    Alt{std::move(t_alt)}
{}
} // namespace ast::node::control
