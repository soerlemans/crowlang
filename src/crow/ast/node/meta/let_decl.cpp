#include "let_decl.hpp"

namespace ast::node::meta {
LetDecl::LetDecl(const std::string_view t_identifier, NodePtr&& t_type)
  : Identifier{t_identifier}, TypeAnnotation{std::move(t_type)}
{}
} // namespace ast::node::meta
