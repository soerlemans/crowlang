#ifndef ACRIS_ACRIS_AST_NODE_FUNCTION_FUNCTION_HPP
#define ACRIS_ACRIS_AST_NODE_FUNCTION_FUNCTION_HPP

// Relative Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"

namespace ast::node::function {
// Using Statements:
using node_traits::AttributeData;
using node_traits::Body;
using node_traits::Identifier;
using node_traits::Params;
using node_traits::TypeAnnotation;
using node_traits::TypeData;

// Classes:
class Function : public Identifier,
                 public Params,
                 public TypeAnnotation,
                 public Body,
                 public TypeData,
                 public AttributeData {
  public:
  Function(std::string_view t_identifier, NodeListPtr&& t_params,
           NodePtr&& t_type, NodeListPtr&& t_body);

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(Function, Identifier, Params,
                                      TypeAnnotation, Body)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Function() = default;
};
} // namespace ast::node::function

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::function, Function);

#endif // ACRIS_ACRIS_AST_NODE_FUNCTION_FUNCTION_HPP
