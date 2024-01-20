#ifndef CROW_AST_NODE_RVALUE_LITERAL_HPP
#define CROW_AST_NODE_RVALUE_LITERAL_HPP

// Includes:
#include "../node_interface.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::rvalue {
// Classes:
template<typename T>
class Literal : public NodeInterface {
  private:
  T m_value;

  protected:
  Literal() = default;

  public:
  friend cereal::access;

  template<typename Archive>
  friend auto serialize(Archive& t_archive, Literal<T>& t_this);

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

// MAKE_ARCHIVEABLE(ast::node::rvalue::Integer, MAKE_NVP(t_this, m_value));
MAKE_ARCHIVEABLE(ast::node::rvalue::Integer, t_this.m_value);

#endif // CROW_AST_NODE_RVALUE_LITERAL_HPP
