#ifndef CROW_AST_NODE_TYPING_IMPL_HPP
#define CROW_AST_NODE_TYPING_IMPL_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::typing {
// Using Statements:
using node_traits::Body;
using node_traits::Identifier;

// Classes:
class Impl : public Identifier, public Body {
  public:
  Impl(std::string_view t_identifier, NodeListPtr&& t_body);

  MAKE_TRAITS_ARCHIVEABLE(Impl, Identifier, Body)
  MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Impl() = default;
};
} // namespace ast::node::typing

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::typing, Impl);

#endif // CROW_AST_NODE_TYPING_IMPL_HPP
