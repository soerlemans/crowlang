#include "ternary.hpp"

namespace ast::node::operators {
Ternary::Ternary(NodePtr&& t_condition, NodePtr&& t_then, NodePtr&& t_alt)
  : Condition{std::move(t_condition)},
    Then{std::move(t_then)},
    Alt{std::move(t_alt)}
{}
} // namespace ast::node::operators
