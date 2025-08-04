#include "function_decl.hpp"

namespace ast::node::meta {
// Methods:
Function::Function(const std::string_view t_identifier, NodeListPtr&& t_params,
                   const std::string_view t_type)
  : Identifier{t_identifier},
    Params{std::move(t_params)},
    TypeAnnotation{t_type}
{}
} // namespace ast::node::meta
