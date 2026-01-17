#include "parameter.hpp"

namespace ast::node::function {
Parameter::Parameter(TextPosition t_pos, const std::string_view t_identifier,
                     NodePtr&& t_type)
  : NodePosition{std::move(t_pos)},
    Identifier{t_identifier},
    TypeAnnotation{std::move(t_type)},
    TypeData{}
{}
} // namespace ast::node::function
