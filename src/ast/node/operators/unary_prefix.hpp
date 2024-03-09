#ifndef CROW_AST_NODE_OPERATORS_UNARY_PREFIX_HPP
#define CROW_AST_NODE_OPERATORS_UNARY_PREFIX_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"

namespace ast::node::operators {
// Using Statements:
using node_traits::Op;
using node_traits::UnaryOperator;

// Enums:
enum class UnaryPrefixOp {
  PLUS,
  MINUS
};

// Classes:
class UnaryPrefix : public Op<UnaryPrefixOp>, public UnaryOperator {
  public:
  UnaryPrefix(UnaryPrefixOp t_op, NodePtr&& t_left);

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(UnaryPrefix, Op<UnaryPrefixOp>,
                                      UnaryOperator)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~UnaryPrefix() = default;
};
} // namespace ast::node::operators

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::operators, UnaryPrefix);
REGISTER_ARCHIVEABLE_TYPE(ast::node::node_traits,
                          Op<ast::node::operators::UnaryPrefixOp>);

#endif // CROW_AST_NODE_OPERATORS_UNARY_PREFIX_HPP
