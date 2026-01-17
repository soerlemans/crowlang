#ifndef ACRIS_ACRIS_AST_NODE_OPERATORS_DECREMENT_HPP
#define ACRIS_ACRIS_AST_NODE_OPERATORS_DECREMENT_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"

namespace ast::node::operators {
// Namespace aliases:
using node_traits::UnaryOperator;

// Classes:
class Decrement : public UnaryOperator {
  public:
  Decrement(NodePtr&& t_left);

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(Decrement, UnaryOperator)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Decrement() = default;
};
} // namespace ast::node::operators

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::operators, Decrement);

#endif // ACRIS_ACRIS_AST_NODE_OPERATORS_DECREMENT_HPP
