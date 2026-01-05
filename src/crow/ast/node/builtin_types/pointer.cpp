#include "member.hpp"

namespace ast::node::user_types {
// Methods:
Member::Member(TextPosition t_pos, const std::string_view t_identifier)
  : NodePosition{std::move(t_pos)}, Identifier{t_identifier}
{}
} // namespace ast::node::user_types
