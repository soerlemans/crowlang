#ifndef CROW_AST_NODE_CONTROL_IF_HPP
#define CROW_AST_NODE_CONTROL_IF_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::control {
// Using Statements:
using container::TextPosition;
using node_traits::Alt;
using node_traits::Condition;
using node_traits::InitExpr;
using node_traits::NodePosition;
using node_traits::Then;

// Classes:
class If : public NodePosition,
           public InitExpr,
           public Condition,
           public Then,
           public Alt {
  public:
  If(TextPosition t_pos, NodePtr&& t_init, NodePtr&& t_condition,
     NodePtr&& t_then, NodePtr&& t_alt);

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(If, NodePosition, InitExpr, Condition, Then, Alt)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~If() = default;
};
} // namespace ast::node::control

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::control, If);

#endif // CROW_AST_NODE_CONTROL_IF_HPP
