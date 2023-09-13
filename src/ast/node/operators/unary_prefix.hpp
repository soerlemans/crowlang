#ifndef CROW_AST_NODE_OPERATORS_UNARY_PREFIX_HPP
#define CROW_AST_NODE_OPERATORS_UNARY_PREFIX_HPP

// Includes:
#include "../../../token/token_type.hpp"

// Local Includes:
#include "fdecl.hpp"
#include "unary_operator.hpp"


namespace ast::node::operators {
// Enums:
enum class UnaryPrefixOp { PLUS, MINUS };

// Classes:
class UnaryPrefix : public UnaryOperator {
  private:
  UnaryPrefixOp m_op;

  public:
  UnaryPrefix(UnaryPrefixOp t_op, NodePtr&& t_left);
  UnaryPrefix(token::TokenType t_tokentype, NodePtr&& t_left);

  virtual auto op() const -> UnaryPrefixOp;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~UnaryPrefix() override = default;
};
} // namespace ast::node::operators

#endif // CROW_AST_NODE_OPERATORS_UNARY_PREFIX_HPP
