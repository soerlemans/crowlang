#ifndef CROW_CROW_AST_NODE_OPERATORS_ARITHMETIC_HPP
#define CROW_CROW_AST_NODE_OPERATORS_ARITHMETIC_HPP

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
enum class ArithmeticOp {
  POWER = 0,

  MULTIPLY,
  DIVIDE,
  MODULO,

  ADD,
  SUBTRACT
};

// Classes:
class Arithmetic : public NodePosition,
                   public Op<ArithmeticOp>,
                   public BinaryOperator,
                   public TypeData {
  public:
  Arithmetic(TextPosition t_pos, ArithmeticOp t_op, NodePtr&& t_left,
             NodePtr&& t_right);

  auto op2str() const -> std::string_view;

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(Arithmetic, NodePosition,
                                      Op<ArithmeticOp>, BinaryOperator)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Arithmetic() = default;
};

// Functions:
/*!
 * Important to note that this function is used in the code generation step.
 * So the translation from enumeration to string should be a valid C++ operator.
 *
 * @param[in] t_op Operator to convert to a string.
 *
 * @return String view of the arithmetic operator, if the given @ref t_op was
 * not found throws.
 */
auto arithmetic_op2str(ArithmeticOp t_op) -> std::string_view;
} // namespace ast::node::operators

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::operators, Arithmetic);
REGISTER_ARCHIVEABLE_TYPE(ast::node::node_traits,
                          Op<ast::node::operators::ArithmeticOp>);

#endif // CROW_CROW_AST_NODE_OPERATORS_ARITHMETIC_HPP
