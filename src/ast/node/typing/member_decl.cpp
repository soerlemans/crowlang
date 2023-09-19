#include "member_decl.hpp"


using namespace ast::node::typing;
using namespace ast::node::node_traits;

MemberDecl::MemberDecl(const std::string_view t_identifier, NodePtr&& t_type)
  : Identifier{t_identifier}, TypeExpr{std::move(t_type)}
{}
