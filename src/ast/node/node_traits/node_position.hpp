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
  NodePosition(TextPosition&& t_pos);

  virtual auto position() -> const TextPosition&;

  VISITABLE_PURE_ACCEPT(visitor::NodeVisitor);

  ~NodePosition() override = default;
};
} // namespace ast::node::node_traits

#endif // CROW_AST_NODE_NODE_TRAITS_NODE_POSITION_HPP
