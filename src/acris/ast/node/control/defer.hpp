#ifndef ACRIS_ACRIS_AST_NODE_CONTROL_DEFER_HPP
#define ACRIS_ACRIS_AST_NODE_CONTROL_DEFER_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"

namespace ast::node::control {
// Aliases:
using node_traits::Body;

// Classes:
class Defer : public Body {
  public:
  Defer(NodeListPtr&& t_body);

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(Defer, Body)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Defer() = default;
};
} // namespace ast::node::control

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::control, Defer);

#endif // ACRIS_ACRIS_AST_NODE_CONTROL_DEFER_HPP
