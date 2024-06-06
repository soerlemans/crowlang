#include "parameter.hpp"

namespace ast::node::function {
Parameter::Parameter(TextPosition t_pos, const std::string_view t_identifier,
                     const std::string_view t_type)
  : NodePosition{std::move(t_pos)},
    Identifier{t_identifier},
    TypeAnnotation{t_type}
{}
} // namespace ast::node::function
