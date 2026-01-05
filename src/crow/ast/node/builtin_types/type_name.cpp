#include "type_name.hpp"

namespace ast::node::builtin_types {
// Methods:
TypeName::TypeName(TextPosition t_pos, const std::string_view t_identifier)
  : NodePosition{std::move(t_pos)}, Identifier{t_identifier}
{}
} // namespace ast::node::user_types
