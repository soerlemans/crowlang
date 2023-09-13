#ifndef CROW_AST_NODE_NODE_TRAITS_CONDITION_HPP
#define CROW_AST_NODE_NODE_TRAITS_CONDITION_HPP

// Includes:
#include "../node_interface.hpp"


namespace ast::node::node_traits {
class Condition : virtual public NodeInterface {
  protected:
  NodePtr m_condition;

  public:
  Condition(NodePtr&& t_condition);

  auto condition() -> NodePtr&;

  auto accept(visitor::NodeVisitor* t_visitor) -> void override = 0;

  ~Condition() override = default;
};
} // namespace ast::node::node_traits

#endif // CROW_AST_NODE_NODE_TRAITS_CONDITION_HPP
