#ifndef CROW_AST_NODE_LVALUE_LET_HPP
#define CROW_AST_NODE_LVALUE_LET_HPP

// STL Includes:
#include <string_view>

// Includes:
#include "../node_interface.hpp"

// Local Includes:
#include "lvalue.hpp"


namespace ast::node::lvalue {
class Let : public NodeInterface {
  private:
  std::string m_identifier;
  NodePtr m_init;

  public:
  Let(std::string_view t_identifier, NodePtr&& t_init);

  auto identifier() const -> std::string_view;
  auto init() -> NodePtr&;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Let() override = default;
};
} // namespace ast::node::lvalue

#endif // CROW_AST_NODE_LVALUE_LET_HPP
