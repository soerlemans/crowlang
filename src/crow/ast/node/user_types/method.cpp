#include "method.hpp"

namespace ast::node::user_types {
Method::Method(const std::string_view t_identifier,
               std::string_view t_receiver_type, NodeListPtr&& t_params,
               const std::string_view t_type, NodeListPtr&& t_body)
  : Identifier{t_identifier},
    Params{std::move(t_params)},
    TypeAnnotation{t_type},
    Body{std::move(t_body)},
    m_receiver_type{t_receiver_type}
{}

auto Method::get_receiver() const -> std::string_view
{
  return m_receiver_type;
}
} // namespace ast::node::user_types
