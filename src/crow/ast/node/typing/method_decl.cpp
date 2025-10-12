#include "method.hpp"

namespace ast::node::typing {
Method::Method(const std::string_view t_identifier, NodeListPtr&& t_params,
               const std::string_view t_type)
  : Identifier{t_identifier},
    Params{std::move(t_params)},
    TypeAnnotation{t_type}
{}
} // namespace ast::node::typing
