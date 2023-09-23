#ifndef CROW_AST_NODE_OPERATORS_COMPARISON_HPP
#define CROW_AST_NODE_OPERATORS_COMPARISON_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::operators {
// Namespace aliases:
namespace nt = node_traits;

// Enums:
enum class ComparisonOp {
  LESS_THAN,
  LESS_THAN_EQUAL,

  EQUAL,
  NOT_EQUAL,

  GREATER_THAN,
  GREATER_THAN_EQUAL,
};

// Classes:
class Comparison : public nt::BinaryOperator {
  private:
  ComparisonOp m_op;

  public:
  Comparison(ComparisonOp t_op, NodePtr&& t_left, NodePtr&& t_right);

  auto op() const -> ComparisonOp;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Comparison() override = default;
};
} // namespace ast::node::operators

#endif // CROW_AST_NODE_OPERATORS_COMPARISON_HPP
