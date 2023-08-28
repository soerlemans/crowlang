#ifndef CROW_AST_NODE_LVALUE_VARIABLE_HPP
#define CROW_AST_NODE_LVALUE_VARIABLE_HPP

// STL Includes:
#include <string_view>

// Includes:
#include "../node_interface.hpp"

// Local Includes:
#include "lvalue.hpp"


namespace ast::node::lvalue {
class Variable : public NodeInterface {
  private:
  std::string m_identifier;

  public:
  Variable(const std::string& t_identifier);

  auto identifier() const -> const std::string&;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Variable() override = default;
};
} // namespace ast::node::lvalue

#endif // CROW_AST_NODE_LVALUE_VARIABLE_HPP
