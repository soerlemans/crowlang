#include "member_decl.hpp"


using namespace ast::node::typing;
using namespace ast::node::node_traits;

MemberDecl::MemberDecl(const std::string_view t_identifier,
                       const std::string_view t_type)
  : Identifier{t_identifier}, TypeAnnotation{t_type}
{}
