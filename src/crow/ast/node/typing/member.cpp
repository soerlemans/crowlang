#include "member.hpp"

namespace ast::node::typing {
// Methods:
Member::Member(TextPosition t_pos, const std::string_view t_identifier)
  : NodePosition{std::move(t_pos)}, Identifier{t_identifier}
{}
} // namespace ast::node::typing
