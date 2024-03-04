#ifndef CROW_AST_NODE_OPERATORS_INCREMENT_HPP
#define CROW_AST_NODE_OPERATORS_INCREMENT_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::operators {
// Using statements:
using node_traits::UnaryOperator;

// Classes:
class Increment : public UnaryOperator {
  private:
  bool m_prefix;

  public:
  Increment(NodePtr&& t_left, bool t_prefix);

  auto prefix() const -> bool;

  MAKE_TRAITS_ARCHIVEABLE(Increment, UnaryOperator)
  MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Increment() = default;
};
} // namespace ast::node::operators

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::operators, Increment);

#endif // CROW_AST_NODE_OPERATORS_INCREMENT_HPP
