#ifndef CROW_AST_NODE_OPERATORS_DECREMENT_HPP
#define CROW_AST_NODE_OPERATORS_DECREMENT_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::operators {
// Namespace aliases:
using node_traits::UnaryOperator;

// Classes:
class Decrement : public UnaryOperator {
  private:
  bool m_prefix;

  public:
  Decrement(NodePtr&& t_left, bool t_prefix);

  auto prefix() const -> bool;

  MAKE_TRAITS_ARCHIVEABLE(Decrement, UnaryOperator)
  MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Decrement() = default;
};
} // namespace ast::node::operators

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::operators, Decrement);

#endif // CROW_AST_NODE_OPERATORS_DECREMENT_HPP
