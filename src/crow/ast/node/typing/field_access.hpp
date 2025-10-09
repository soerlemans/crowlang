#ifndef CROW_CROW_AST_NODE_TYPING_DOT_EXPR_HPP
#define CROW_CROW_AST_NODE_TYPING_DOT_EXPR_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"

namespace ast::node::typing {
// Using Statements:
using container::TextPosition;
using node_traits::BinaryOperator;
using node_traits::NodePosition;
using node_traits::TypeData;

// Classes:
class FieldAccess : public NodePosition,
                    public BinaryOperator,
                    public TypeData {
  public:
  FieldAccess(TextPosition t_pos, NodePtr&& t_left, NodePtr&& t_right);

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(FieldAccess, NodePosition, BinaryOperator)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~FieldAccess() = default;
};
} // namespace ast::node::typing

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::typing, FieldAccess);

#endif // CROW_CROW_AST_NODE_TYPING_DOT_EXPR_HPP
