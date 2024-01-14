#ifndef CROW_AST_NODE_FUNCTION_FUNCTION_HPP
#define CROW_AST_NODE_FUNCTION_FUNCTION_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::function {
// Using Statements:
using node_traits::Body;
using node_traits::Identifier;
using node_traits::Params;
using node_traits::TypeAnnotation;
using node_traits::typing::TypeData;

// Classes:
class Function : public Identifier,
                 public Params,
                 public TypeAnnotation,
                 public Body,
                 public TypeData {
  public:
  Function(std::string_view t_identifier, NodeListPtr&& t_params,
           std::string_view t_type, NodeListPtr&& t_body);

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Function() override = default;
};
} // namespace ast::node::function

#endif // CROW_AST_NODE_FUNCTION_FUNCTION_HPP
