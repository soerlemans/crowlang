#ifndef CROW_CROW_AST_NODE_LVALUE_VARIABLE_HPP
#define CROW_CROW_AST_NODE_LVALUE_VARIABLE_HPP

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

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(Variable, NodePosition, Identifier,
                                      TypeAnnotation)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Variable() = default;
};
} // namespace ast::node::lvalue

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::lvalue, Variable);

#endif // CROW_CROW_AST_NODE_LVALUE_VARIABLE_HPP
