#ifndef CROW_AST_NODE_LVALUE_VARIABLE_HPP
#define CROW_AST_NODE_LVALUE_VARIABLE_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::lvalue {
// Aliases:
namespace nt = node_traits;
namespace ct = container;

// Classes:
class Variable : public nt::NodePosition,
                 public nt::Identifier,
                 public nt::Type {
  public:
  Variable(ct::TextPosition t_pos, std::string_view t_identifier);
  Variable(ct::TextPosition t_pos, std::string_view t_identifier,
           std::string_view t_type);

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Variable() override = default;
};
} // namespace ast::node::lvalue

#endif // CROW_AST_NODE_LVALUE_VARIABLE_HPP
