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
  private:
  std::string m_receiver_type;

  public:
  Method(std::string_view t_identifier, std::string_view t_receiver_type,
         NodeListPtr&& t_params, std::string_view t_type, NodeListPtr&& t_body);

  // TODO: replace the receiver being a string with something more elegant.
  // Maybe its own node type?
	// Something like Receiver which has its own type annotation and type data?
  auto get_receiver() const -> std::string_view;

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(Method, Identifier, Params,
                                      TypeAnnotation, Body)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Method() = default;
};
} // namespace ast::node::typing

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::typing, Method);

#endif // CROW_CROW_AST_NODE_TYPING_METHOD_HPP
