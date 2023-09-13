#ifndef CROW_AST_NODE_NODE_TRAITS_INIT_HPP
#define CROW_AST_NODE_NODE_TRAITS_INIT_HPP

// Includes:
#include "../node_interface.hpp"


namespace ast::node::node_traits {
class Init : public NodeInterface {
  protected:
  NodePtr m_init;

  public:
  Init(NodePtr&& t_init);

  auto init() -> NodePtr&;

  auto accept(visitor::NodeVisitor* t_visitor) -> void override = 0;

  ~Init() override = default;
};
} // namespace ast::node::node_traits


#endif // CROW_AST_NODE_NODE_TRAITS_INIT_HPP
