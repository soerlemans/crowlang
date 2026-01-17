#include "var_decl.hpp"

namespace ast::node::meta {
VarDecl::VarDecl(const std::string_view t_identifier, NodePtr&& t_type)
  : Identifier{t_identifier}, TypeAnnotation{std::move(t_type)}
{}
} // namespace ast::node::meta
