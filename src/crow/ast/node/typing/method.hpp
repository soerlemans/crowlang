#ifndef CROW_CROW_AST_NODE_TYPING_METHOD_HPP
#define CROW_CROW_AST_NODE_TYPING_METHOD_HPP


// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"
#include <string_view>

namespace ast::node::typing {
// Using Statements:
using node_traits::AttributeData;
using node_traits::Body;
using node_traits::Identifier;
using node_traits::Params;
using node_traits::TypeAnnotation;
using node_traits::TypeData;

// Classes:
class Method : public Identifier,
               public Params,
               public TypeAnnotation,
               public Body,
               public TypeData,
               public AttributeData {
  public:
  Method(std::string_view t_identifier, NodeListPtr&& t_params,
         std::string_view t_type, NodeListPtr&& t_body);

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(Method, Identifier, Params,
                                      TypeAnnotation, Body)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Method() = default;
};
} // namespace ast::node::typing

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::typing, Method);

#endif // CROW_CROW_AST_NODE_TYPING_METHOD_HPP
