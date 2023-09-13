#ifndef CROW_AST_NODE_LVALUE_VARIABLE_HPP
#define CROW_AST_NODE_LVALUE_VARIABLE_HPP

// STL Includes:
#include <string_view>

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::lvalue {
namespace nt = node_traits;

class Variable : public nt::Identifier {
  private:
  std::string m_type;

  public:
  Variable(std::string_view t_identifier);
  Variable(std::string_view t_identifier, std::string_view t_type);

  auto type() const -> std::string_view;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Variable() override = default;
};
} // namespace ast::node::lvalue

#endif // CROW_AST_NODE_LVALUE_VARIABLE_HPP
