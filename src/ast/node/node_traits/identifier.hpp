#ifndef CROW_AST_NODE_NODE_TRAITS_IDENTIFIER_HPP
#define CROW_AST_NODE_NODE_TRAITS_IDENTIFIER_HPP

// STL Includes:
#include <string_view>

// Includes:
#include "../node_interface.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::node_traits {
class Identifier : virtual public NodeInterface {
  protected:
  std::string m_identifier;

  public:
  Identifier(std::string_view t_identifier);

  virtual auto identifier() const -> std::string_view;

  MAKE_ARCHIVEABLE(Identifier)
  {
		t_archive(CEREAL_NVP(m_identifier));
	}

  VISITABLE_PURE_ACCEPT(visitor::NodeVisitor);

  virtual ~Identifier() = default;
};
} // namespace ast::node::node_traits

// Cereal register type:
REGISTER_ARCHIVEABLE_TYPE(ast::node::node_traits, Identifier);

#endif // CROW_AST_NODE_NODE_TRAITS_IDENTIFIER_HPP
