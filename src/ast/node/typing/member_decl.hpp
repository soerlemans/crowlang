#ifndef CROW_AST_NODE_TYPING_MEMBER_DECL_HPP
#define CROW_AST_NODE_TYPING_MEMBER_DECL_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::typing {
// Aliases:
namespace nt = node_traits;

// Classes:
class MemberDecl : public nt::Identifier, public nt::TypeAnnotation {
  public:
  MemberDecl(std::string_view t_identifier, std::string_view t_type);

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~MemberDecl() override = default;
};
} // namespace ast::node::typing

#endif // CROW_AST_NODE_TYPING_MEMBER_DECL_HPP
