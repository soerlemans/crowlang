#ifndef SUBSCRIPT_HPP
#define SUBSCRIPT_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"

namespace ast::node::lvalue {
// Aliases:
using container::TextPosition;
using node_traits::NodePosition;
using node_traits::TypeData;
using node_traits::BinaryOperator;

// Classes:
class Subscript : public NodePosition, public BinaryOperator, public TypeData {
  public:
  Subscript(TextPosition t_pos, NodePtr&& t_expr, NodePtr&& t_index);

  // AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(Subscript, NodePosition, )
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Subscript() = default;
};
} // namespace ast::node::lvalue

// Cereal type registration:
// REGISTER_ARCHIVEABLE_TYPE(ast::node::lvalue, Subscript);


#endif // SUBSCRIPT_HPP
