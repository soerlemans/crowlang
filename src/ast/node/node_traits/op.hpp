#ifndef CROW_AST_NODE_NODE_TRAITS_OP_HPP
#define CROW_AST_NODE_NODE_TRAITS_OP_HPP

// Includes:
#include "../node_interface.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::node_traits {
template<typename T>
class Op : virtual public NodeInterface {
  protected:
  T m_op;

  public:
  Op(const T t_op): m_op{t_op}
  {}

  virtual auto op() const -> T
  {
    return m_op;
  }

  MAKE_ARCHIVEABLE(Op)
  {
    t_archive(m_op);
  }

  VISITABLE_PURE_ACCEPT(visitor::NodeVisitor);

  virtual ~Op() = default;
};
} // namespace ast::node::node_traits

#endif // CROW_AST_NODE_NODE_TRAITS_OP_HPP
