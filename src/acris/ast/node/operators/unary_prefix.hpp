#ifndef ACRIS_ACRIS_AST_NODE_OPERATORS_UNARY_PREFIX_HPP
#define ACRIS_ACRIS_AST_NODE_OPERATORS_UNARY_PREFIX_HPP

// Absolute Includes:
#include "acris/token/token_type.hpp"

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
  /*!
   * Constructor will throw if given inconvertible @ref TokenType.
   */
  UnaryPrefix(token::TokenType t_op, NodePtr&& t_left);
  UnaryPrefix(UnaryPrefixOp t_op, NodePtr&& t_left);

  auto op2str() const -> std::string_view override;

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(UnaryPrefix, Op<UnaryPrefixOp>,
                                      UnaryOperator)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~UnaryPrefix() = default;
};

// Functions:
/*!
 * Converts a @ref TokenType to a @ref UnaryPrefixOp.
 * If the conversion is not possible throws.
 */
auto token_type2unary_prefix_op(token::TokenType t_type) -> UnaryPrefixOp;

/*!
 * Important to note that this function is used in the code generation step.
 * So the translation from enumeration to string should be a valid C++ operator.
 *
 * @param[in] t_op Operator to convert to a string.
 *
 * @return String view of the unary prefix operator, if the given @ref t_op was
 * not found throws.
 */
auto unary_prefix_op2str(UnaryPrefixOp t_op) -> std::string_view;
} // namespace ast::node::operators

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::operators, UnaryPrefix);
REGISTER_ARCHIVEABLE_TYPE(ast::node::node_traits,
                          Op<ast::node::operators::UnaryPrefixOp>);

#endif // ACRIS_ACRIS_AST_NODE_OPERATORS_UNARY_PREFIX_HPP
