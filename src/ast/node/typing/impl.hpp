#ifndef CROW_AST_NODE_TYPING_IMPL_HPP
#define CROW_AST_NODE_TYPING_IMPL_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::typing {
// Aliases:
namespace nt = node_traits;

// Classes:
class Impl : public nt::Identifier, public nt::Body {
  public:
  Impl(std::string_view t_identifier, NodeListPtr&& t_body);

  MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Impl() = default;
};
} // namespace ast::node::typing

#endif // CROW_AST_NODE_TYPING_IMPL_HPP
