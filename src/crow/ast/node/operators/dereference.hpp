#ifndef CROW_CROW_AST_NODE_OPERATORS_DEREFERENCE_HPP
#define CROW_CROW_AST_NODE_OPERATORS_DEREFERENCE_HPP

// Absolute Includes:
#include "crow/token/token_type.hpp"

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"

namespace ast::node::operators {
// Using Statements:
using node_traits::UnaryOperator;

// Classes:
class Dereference : public UnaryOperator {
  public:
  Dereference(NodePtr&& t_left);

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(Dereference, UnaryOperator)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Dereference() = default;
};
} // namespace ast::node::operators

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::operators, Dereference);

#endif // CROW_CROW_AST_NODE_OPERATORS_DEREFERENCE_HPP
