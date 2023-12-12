#ifndef CROW_AST_NODE_CONTROL_IF_HPP
#define CROW_AST_NODE_CONTROL_IF_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::control {
// Aliases:
namespace nt = node_traits;
namespace ct = container;

// Classes:
class If : public nt::NodePosition,
           public nt::InitExpr,
           public nt::Condition,
           public nt::Then,
           public nt::Alt {
  public:
  If(ct::TextPosition t_pos, NodePtr&& t_init,
     NodePtr&& t_condition, NodePtr&& t_then, NodePtr&& t_alt);

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~If() override = default;
};
} // namespace ast::node::control

#endif // CROW_AST_NODE_CONTROL_IF_HPP
