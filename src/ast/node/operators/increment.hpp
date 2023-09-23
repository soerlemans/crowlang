#ifndef CROW_AST_NODE_OPERATORS_INCREMENT_HPP
#define CROW_AST_NODE_OPERATORS_INCREMENT_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::operators {
// Namespace aliases:
namespace nt = node_traits;

// Classes:
class Increment : public nt::UnaryOperator {
  private:
  bool m_prefix;

  public:
  Increment(NodePtr&& t_left, bool t_prefix);

  auto prefix() const -> bool;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Increment() override = default;
};
} // namespace ast::node::operators

#endif
