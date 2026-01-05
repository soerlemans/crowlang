#include "member_decl.hpp"

namespace ast::node::user_types {
MemberDecl::MemberDecl(const std::string_view t_identifier,
                       const std::string_view t_type)
  : Identifier{t_identifier}, TypeAnnotation{t_type}, TypeData{}
{}
} // namespace ast::node::user_types
