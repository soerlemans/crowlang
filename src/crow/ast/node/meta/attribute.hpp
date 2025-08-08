#ifndef CROW_CROW_AST_NODE_META_ATTRIBUTE_HPP
#define CROW_CROW_AST_NODE_META_ATTRIBUTE_HPP

// Relative Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"

namespace ast::node::meta {
// Using:
using node_traits::AttributeData;
using node_traits::Body;
using node_traits::Identifier;
using node_traits::Params;

// Classes:
class Attribute : public Identifier, public Params, public Body, AttributeData {
  public:
  Attribute(std::string_view t_identifier, NodeListPtr&& t_params,
            NodeListPtr&& t_body);

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(Attribute, Identifier, Params)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Attribute() = default;
};
} // namespace ast::node::meta

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::meta, Attribute);

#endif // CROW_CROW_AST_NODE_META_ATTRIBUTE_HPP
