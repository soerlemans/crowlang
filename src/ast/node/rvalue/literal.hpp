#ifndef CROW_AST_NODE_RVALUE_LITERAL_HPP
#define CROW_AST_NODE_RVALUE_LITERAL_HPP

// Includes:
#include "../../types.hpp"
#include "../node.hpp"
#include "../node_interface.hpp"


namespace ast::node::rvalue {
// Classes:
template<typename T>
class Literal : public NodeInterface {
  private:
  T m_value;

  public:
  Literal(const T t_value): m_value{t_value}
  {}

  auto get() -> T
  {
    return m_value;
  }

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Literal() override = default;
};
} // namespace ast::node::rvalue

#endif // CROW_AST_NODE_RVALUE_LITERAL_HPP
