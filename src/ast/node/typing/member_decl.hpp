#ifndef MEMBER_DECL_HPP
#define MEMBER_DECL_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::typing {
// Aliases:
namespace nt = node_traits;

// Classes:
class MemberDecl : public nt::Identifier, public nt::TypeExpr {
  public:
  MemberDecl(std::string_view t_identifier, NodePtr&& t_type);

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~MemberDecl() override = default;
};
} // namespace ast::node::typing

#endif // MEMBER_DECL_HPP
