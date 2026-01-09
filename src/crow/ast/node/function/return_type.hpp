#ifndef CROW_CROW_AST_NODE_FUNCTION_RETURN_TYPE_HPP
#define CROW_CROW_AST_NODE_FUNCTION_RETURN_TYPE_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"

namespace ast::node::function {
// Using Statements:
using node_traits::TypeAnnotation;
using node_traits::TypeData;

// Classes:
class ReturnType : public TypeAnnotation, public TypeData {
  public:
  ReturnType(NodePtr&& t_type);

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(ReturnType, TypeAnnotation)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~ReturnType() = default;
};
} // namespace ast::node::function

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::function, ReturnType);

#endif // CROW_CROW_AST_NODE_FUNCTION_RETURN_TYPE_HPP
