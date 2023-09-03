#ifndef CROW_AST_NODE_LVALUE_LET_HPP
#define CROW_AST_NODE_LVALUE_LET_HPP

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
  Let(const std::string& t_identifier, NodePtr&& t_init);

  auto identifier() const -> const std::string&;
  auto init() -> NodePtr&;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Let() override = default;
};
} // namespace ast::node::lvalue

#endif // CROW_AST_NODE_LVALUE_LET_HPP
