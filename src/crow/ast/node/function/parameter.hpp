#ifndef CROW_CROW_AST_NODE_FUNCTION_PARAMETER_HPP
#define CROW_CROW_AST_NODE_FUNCTION_PARAMETER_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"

namespace ast::node::function {
// Using Statements:
using container::TextPosition;
using node_traits::Identifier;
using node_traits::NodePosition;
using node_traits::TypeAnnotation;

// Classes:
class Parameter : public NodePosition,
                  public Identifier,
                  public TypeAnnotation {
  public:
  Parameter(TextPosition t_pos, std::string_view t_identifier,
            std::string_view t_type);

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(Parameter, NodePosition, Identifier,
                                      TypeAnnotation)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Parameter() = default;
};
} // namespace ast::node::function

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::function, Parameter);

#endif // CROW_CROW_AST_NODE_FUNCTION_PARAMETER_HPP
