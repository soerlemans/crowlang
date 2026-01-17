#ifndef ACRIS_ACRIS_AST_NODE_LVALUE_VARIABLE_HPP
#define ACRIS_ACRIS_AST_NODE_LVALUE_VARIABLE_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"

namespace ast::node::lvalue {
// Aliases:
using container::TextPosition;
using node_traits::Identifier;
using node_traits::NodePosition;
using node_traits::TypeData;

// Classes:
class Variable : public NodePosition, public Identifier, public TypeData {
  public:
  Variable(TextPosition t_pos, std::string_view t_identifier);

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(Variable, NodePosition, Identifier)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Variable() = default;
};
} // namespace ast::node::lvalue

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::lvalue, Variable);

#endif // ACRIS_ACRIS_AST_NODE_LVALUE_VARIABLE_HPP
