#ifndef CROW_AST_NODE_NODE_TRAITS_POSITION_HPP
#define CROW_AST_NODE_NODE_TRAITS_POSITION_HPP


// Includes:
#include "../../../container/text_position.hpp"
#include "../node_interface.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::node_traits {
//! Contains the original position of the Node in the Crow source code
class NodePosition : virtual public NodeInterface {
  protected:
  container::TextPosition m_pos;

  public:
  NodePosition(container::TextPosition t_pos);

  virtual auto position() -> const container::TextPosition&;

  VISITABLE_PURE_ACCEPT(visitor::NodeVisitor);

  ~NodePosition() override = default;
};
} // namespace ast::node::node_traits

#endif // CROW_AST_NODE_NODE_TRAITS_POSITION_HPP
