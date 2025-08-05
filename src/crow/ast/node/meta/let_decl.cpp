#include "let_decl.hpp"

namespace ast::node::meta {
LetDecl::LetDecl(const std::string_view t_identifier,
                 const std::string_view t_type)
  : Identifier{t_identifier}, TypeAnnotation{t_type}
{}
} // namespace ast::node::meta
