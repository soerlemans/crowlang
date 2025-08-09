#include "attribute.hpp"

namespace ast::node::meta {
// Methods:
Attribute::Attribute(const std::string_view t_identifier,
                     NodeListPtr&& t_params, NodeListPtr&& t_body)
  : Identifier{t_identifier},
    Params{std::move(t_params)},
    Body{std::move(t_body)}
{}
} // namespace ast::node::meta
