#ifndef ACRIS_ACRIS_AST_NODE_OPERATORS_TERNARY_HPP
#define ACRIS_ACRIS_AST_NODE_OPERATORS_TERNARY_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"

namespace ast::node::operators {
// Using Statements:
using node_traits::Alt;
using node_traits::Condition;
using node_traits::Then;

// Classes:
class Ternary : public Condition, public Then, public Alt {
  public:
  explicit Ternary(NodePtr&& t_condition, NodePtr&& t_then, NodePtr&& t_alt);

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(Ternary, Condition, Then, Alt)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Ternary() = default;
};
} // namespace ast::node::operators

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::operators, Ternary);

#endif // ACRIS_ACRIS_AST_NODE_OPERATORS_TERNARY_HPP
