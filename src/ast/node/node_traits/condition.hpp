#ifndef CROW_AST_NODE_NODE_TRAITS_CONDITION_HPP
#define CROW_AST_NODE_NODE_TRAITS_CONDITION_HPP

// Includes:
#include "../node_interface.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::node_traits {
class Condition : virtual public NodeInterface {
  protected:
  NodePtr m_condition;

  public:
  Condition(NodePtr&& t_condition);

  virtual auto condition() -> NodePtr&;

  VISITABLE_PURE_ACCEPT(visitor::NodeVisitor);

  virtual ~Condition() = default;
};
} // namespace ast::node::node_traits

#endif // CROW_AST_NODE_NODE_TRAITS_CONDITION_HPP
