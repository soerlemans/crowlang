#include "member_access.hpp"

namespace ast::node::user_types {
MemberAccess::MemberAccess(TextPosition t_pos, NodePtr&& t_left,
                           NodePtr&& t_right)
  : NodePosition{std::move(t_pos)},
    BinaryOperator{std::move(t_left), std::move(t_right)},
    TypeData{}
{}
} // namespace ast::node::user_types
