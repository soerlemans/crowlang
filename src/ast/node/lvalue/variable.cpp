#include "variable.hpp"


namespace ast::node::lvalue {
// Methods:
Variable::Variable(TextPosition t_pos, const std::string_view t_identifier)
  : NodePosition{std::move(t_pos)}, Identifier{t_identifier}, TypeAnnotation{""}
{}

Variable::Variable(TextPosition t_pos, std::string_view t_identifier,
                   std::string_view t_type)
  : NodePosition{std::move(t_pos)},
    Identifier{t_identifier},
    TypeAnnotation{t_type}
{}
} // namespace ast::node::lvalue
