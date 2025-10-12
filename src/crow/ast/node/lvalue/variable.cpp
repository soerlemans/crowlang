#include "variable.hpp"

namespace ast::node::lvalue {
// Methods:
Variable::Variable(TextPosition t_pos, const std::string_view t_identifier)
  : NodePosition{std::move(t_pos)}, Identifier{t_identifier}
{}
} // namespace ast::node::lvalue
