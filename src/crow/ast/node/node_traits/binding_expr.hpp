#ifndef CROW_CROW_AST_NODE_NODE_TRAITS_DECL_EXPR_HPP
#define CROW_CROW_AST_NODE_NODE_TRAITS_DECL_EXPR_HPP

// Includes:
#include "../include.hpp"

// Local Includes:
#include "attribute_data.hpp"
#include "fdecl.hpp"
#include "identifier.hpp"
#include "init_expr.hpp"
#include "node_position.hpp"
#include "type_annotation.hpp"
#include "type_data.hpp"

namespace ast::node::node_traits {
// Using Statements:
using container::TextPosition;

// Classes:
class BindingExpr : public NodePosition,
                 public Identifier,
                 public TypeAnnotation,
                 public TypeData,
                 public AttributeData,
                 public InitExpr {
  public:
  BindingExpr(TextPosition&& t_pos, std::string_view t_identifier,
           std::string_view t_type, NodePtr&& t_init);

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(BindingExpr, NodePosition, Identifier,
                                      TypeAnnotation, InitExpr)
  AST_VISITOR_VISITABLE_PURE_ACCEPT(visitor::NodeVisitor);

  virtual ~BindingExpr() = default;
};
} // namespace ast::node::node_traits

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::node_traits, BindingExpr);

#endif // CROW_CROW_AST_NODE_NODE_TRAITS_DECL_EXPR_HPP
