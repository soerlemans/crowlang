#ifndef CROW_AST_NODE_OPERATORS_UNARY_PREFIX_HPP
#define CROW_AST_NODE_OPERATORS_UNARY_PREFIX_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::operators {
// Namespace aliases:
namespace nt = node_traits;

// Enums:
enum class UnaryPrefixOp { PLUS, MINUS };

// Classes:
class UnaryPrefix : public nt::UnaryOperator {
  private:
  UnaryPrefixOp m_op;

  public:
  UnaryPrefix(UnaryPrefixOp t_op, NodePtr&& t_left);

  virtual auto op() const -> UnaryPrefixOp;

  MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~UnaryPrefix() = default;
};
} // namespace ast::node::operators

#endif // CROW_AST_NODE_OPERATORS_UNARY_PREFIX_HPP
