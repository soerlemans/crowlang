#ifndef CROW_AST_NODE_NODE_TRAITS_TYPE_ANNOTATION_HPP
#define CROW_AST_NODE_NODE_TRAITS_TYPE_ANNOTATION_HPP

// STL Includes:
#include <string_view>

// Includes:
#include "../include.hpp"

// Local Includes:
#include "fdecl.hpp"

namespace ast::node::node_traits {
class TypeAnnotation : virtual public NodeInterface {
  protected:
  std::string m_type;

  public:
  TypeAnnotation() = default;
  TypeAnnotation(std::string_view t_type);

  virtual auto type() const -> std::string_view;

  template<typename Archive>
  auto serialize(Archive& t_archive) -> void
  {
    t_archive(m_type);
  }

  AST_VISITOR_VISITABLE_PURE_ACCEPT(visitor::NodeVisitor);

  virtual ~TypeAnnotation() = default;
};
} // namespace ast::node::node_traits

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::node_traits, TypeAnnotation);

#endif // CROW_AST_NODE_NODE_TRAITS_TYPE_ANNOTATION_HPP
