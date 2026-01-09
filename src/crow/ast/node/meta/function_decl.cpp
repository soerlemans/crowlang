#include "function_decl.hpp"

namespace ast::node::meta {
// Methods:
FunctionDecl::FunctionDecl(const std::string_view t_identifier,
                           NodeListPtr&& t_params, NodePtr&& t_type)
  : Identifier{t_identifier},
    Params{std::move(t_params)},
    TypeAnnotation{std::move(t_type)}
{}
} // namespace ast::node::meta
