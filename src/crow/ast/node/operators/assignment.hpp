#ifndef CROW_CROW_AST_NODE_OPERATORS_ASSIGNMENT_HPP
#define CROW_CROW_AST_NODE_OPERATORS_ASSIGNMENT_HPP

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
enum AssignmentOp {
  MULTIPLY = 0,
  DIVIDE,
  MODULO,

  ADD,
  SUBTRACT,

  REGULAR
};

// Classes:
class Assignment : public NodePosition,
                   public Op<AssignmentOp>,
                   public BinaryOperator,
                   public TypeData {
  public:
  Assignment(TextPosition t_pos, AssignmentOp t_op, NodePtr&& t_left,
             NodePtr&& t_right);

  auto op2str() const -> std::string_view override;

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(Assignment, NodePosition,
                                      Op<AssignmentOp>, BinaryOperator)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Assignment() = default;
};

// Functions:
/*!
 * Important to note that this function is used in the code generation step.
 * So the translation from enumeration to string should be a valid C++ operator.
 *
 * @param[in] t_op Operator to convert to a string.
 *
 * @return String view of the assignment operator, if the given @ref t_op was
 * not found throws.
 */
auto assignment_op2str(AssignmentOp t_op) -> std::string_view;
} // namespace ast::node::operators

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::operators, Assignment);
REGISTER_ARCHIVEABLE_TYPE(ast::node::node_traits,
                          Op<ast::node::operators::AssignmentOp>);

#endif // CROW_CROW_AST_NODE_OPERATORS_ASSIGNMENT_HPP
