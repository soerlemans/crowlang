#ifndef ACRIS_ACRIS_AST_NODE_NODE_TRAITS_IDENTIFIER_HPP
#define ACRIS_ACRIS_AST_NODE_NODE_TRAITS_IDENTIFIER_HPP

// STL Includes:
#include <string_view>

// Includes:
#include "../include.hpp"

// Local Includes:
#include "fdecl.hpp"

namespace ast::node::node_traits {
class Identifier : virtual public NodeInterface {
  private:
  std::string m_identifier;

  public:
  Identifier(std::string_view t_identifier);

  auto identifier() const -> std::string_view;

  AST_ARCHIVE_MAKE_ARCHIVEABLE(Identifier)
  {
    t_archive(CEREAL_NVP(m_identifier));
  }

  AST_VISITOR_VISITABLE_PURE_ACCEPT(visitor::NodeVisitor);

  virtual ~Identifier() = default;
};
} // namespace ast::node::node_traits

// Cereal register type:
REGISTER_ARCHIVEABLE_TYPE(ast::node::node_traits, Identifier);

#endif // ACRIS_ACRIS_AST_NODE_NODE_TRAITS_IDENTIFIER_HPP
