#include "parameter.hpp"


using namespace ast::node::function;
using namespace ast::node::node_traits;

Parameter::Parameter(ct::TextPosition t_pos, std::string_view t_identifier,
                     std::string_view t_type)
  : NodePosition{std::move(t_pos)},
    Identifier{t_identifier},
    TypeAnnotation{t_type}
{}
