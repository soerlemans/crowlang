#ifndef CROW_AST_NODE_FUNCTION_RETURN_TYPE_HPP
#define CROW_AST_NODE_FUNCTION_RETURN_TYPE_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::function {
// Using Statements:
using node_traits::TypeAnnotation;

// Classes:
class ReturnType : public TypeAnnotation {
  public:
  ReturnType(std::string_view t_type);

  MAKE_TRAITS_ARCHIVEABLE(ReturnType, TypeAnnotation)
  MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~ReturnType() = default;
};
} // namespace ast::node::function

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::function, ReturnType);

#endif // CROW_AST_NODE_FUNCTION_RETURN_TYPE_HPP
