#ifndef CROW_AST_NODE_LVALUE_VARIABLE_HPP
#define CROW_AST_NODE_LVALUE_VARIABLE_HPP

#include <string_view>

#include "../node_interface.hpp"

#include "lvalue.hpp"


namespace node::lvalue {
class Variable : public NodeInterface {
  private:
  std::string m_identifier;

  public:
  Variable(const std::string& t_identifier);

  auto identifier() const -> const std::string&;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Variable() override = default;
};
} // namespace node::lvalue

#endif // CROW_AST_NODE_LVALUE_VARIABLE_HPP
