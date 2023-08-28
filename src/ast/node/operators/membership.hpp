#ifndef CROW_AST_NODE_OPERATORS_MEMBERSHIP_HPP
#define CROW_AST_NODE_OPERATORS_MEMBERSHIP_HPP

#include "operators.hpp"
#include "unary_operator.hpp"


namespace node::operators {
class Membership : public UnaryOperator {
  private:
  std::string m_name;

  public:
  Membership(NodePtr&& t_lhs, std::string&& t_name);

  auto name() const -> std::string_view;
  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Membership() override = default;
};
} // namespace node::operators

#endif // CROW_AST_NODE_OPERATORS_MEMBERSHIP_HPP
