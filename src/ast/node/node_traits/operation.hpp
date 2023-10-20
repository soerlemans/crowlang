#ifndef OPERATION_HPP
#define OPERATION_HPP

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

  VISITABLE_PURE_ACCEPT(visitor::NodeVisitor);

  ~Op() override = default;
};
} // namespace ast::node::node_traits

#endif // OPERATION_HPP
