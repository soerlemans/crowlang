#include "member_decl.hpp"

namespace ast::node::user_types {
MemberDecl::MemberDecl(const std::string_view t_identifier, NodePtr&& t_type)
  : Identifier{t_identifier}, TypeAnnotation{std::move(t_type)}, TypeData{}
{}
} // namespace ast::node::user_types
