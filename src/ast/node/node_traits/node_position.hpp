#ifndef CROW_AST_NODE_NODE_TRAITS_NODE_POSITION_HPP
#define CROW_AST_NODE_NODE_TRAITS_NODE_POSITION_HPP


// Includes:
#include "../../../container/text_position.hpp"
#include "../node_interface.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::node_traits {
// Using Statements:
using container::TextPosition;

// Classes:
//! Contains the original position of the Node in the Crow source code
class NodePosition : virtual public NodeInterface {
  protected:
  TextPosition m_pos;

  public:
  NodePosition() = default;
  NodePosition(TextPosition&& t_pos);

  virtual auto position() -> const TextPosition&;

  template<typename Archive>
  auto serialize(Archive& t_archive) -> void
  {
    t_archive(CEREAL_NVP(m_pos.m_source), CEREAL_NVP(m_pos.m_line),
              CEREAL_NVP(m_pos.m_lineno), CEREAL_NVP(m_pos.m_columno));
  }

  VISITABLE_PURE_ACCEPT(visitor::NodeVisitor);

  virtual ~NodePosition() = default;
};
} // namespace ast::node::node_traits

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::node_traits, NodePosition);

#endif // CROW_AST_NODE_NODE_TRAITS_NODE_POSITION_HPP
