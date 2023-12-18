#ifndef CROW_AST_NODE_LVALUE_VARIABLE_HPP
#define CROW_AST_NODE_LVALUE_VARIABLE_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::lvalue {
// Aliases:
using container::TextPosition;
using node_traits::Identifier;
using node_traits::NodePosition;
using node_traits::TypeAnnotation;
using node_traits::typing::TypeData;

// Classes:
class Variable : public NodePosition,
                 public Identifier,
                 public TypeAnnotation,
                 public TypeData {
  public:
  Variable(TextPosition t_pos, std::string_view t_identifier);
  Variable(TextPosition t_pos, std::string_view t_identifier,
           std::string_view t_type);

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Variable() override = default;
};
} // namespace ast::node::lvalue

#endif // CROW_AST_NODE_LVALUE_VARIABLE_HPP
