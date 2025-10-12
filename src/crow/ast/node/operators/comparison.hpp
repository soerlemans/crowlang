#ifndef CROW_CROW_AST_NODE_OPERATORS_COMPARISON_HPP
#define CROW_CROW_AST_NODE_OPERATORS_COMPARISON_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"

namespace ast::node::operators {
// Using Statements:
using container::TextPosition;
using node_traits::BinaryOperator;
using node_traits::NodePosition;
using node_traits::Op;
using node_traits::TypeData;

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
class Comparison : public NodePosition,
                   public Op<ComparisonOp>,
                   public BinaryOperator,
                   public TypeData {
  public:
  Comparison(TextPosition t_pos, ComparisonOp t_op, NodePtr&& t_left,
             NodePtr&& t_right);

  auto op2str() const -> std::string_view;

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(Comparison, NodePosition,
                                      Op<ComparisonOp>, BinaryOperator)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Comparison() = default;
};

// Functions:
/*!
 * Important to note that this function is used in the code generation step.
 * So the translation from enumeration to string should be a valid C++ operator.
 *
 * @param[in] t_op Operator to convert to a string.
 *
 * @return String view of the comparison operator, if the given @ref t_op was
 * not found throws.
 */
auto comparison_op2str(ComparisonOp t_op) -> std::string_view;
} // namespace ast::node::operators

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::operators, Comparison);
REGISTER_ARCHIVEABLE_TYPE(ast::node::node_traits,
                          Op<ast::node::operators::ComparisonOp>);

#endif // CROW_CROW_AST_NODE_OPERATORS_COMPARISON_HPP
