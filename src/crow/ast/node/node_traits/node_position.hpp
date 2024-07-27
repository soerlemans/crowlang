#ifndef CROW_CROW_AST_NODE_NODE_TRAITS_NODE_POSITION_HPP
#define CROW_CROW_AST_NODE_NODE_TRAITS_NODE_POSITION_HPP


// Includes:
#include "../include.hpp"
#include "crow/container/text_position.hpp"

// Local Includes:
#include "fdecl.hpp"

namespace ast::node::node_traits {
// Using Statements:
using container::TextPosition;

// Classes:
//! Contains the original position of the Node in the Crow source code
class NodePosition : virtual public NodeInterface {
  private:
  TextPosition m_pos;

  public:
  NodePosition() = default;
  NodePosition(TextPosition&& t_pos);

  auto position() -> const TextPosition&;

  template<typename Archive>
  auto serialize(Archive& t_archive) -> void
  {
    t_archive(cereal::make_nvp("m_source", m_pos.m_source),
              cereal::make_nvp("m_line", m_pos.m_line),
              cereal::make_nvp("m_lineno", m_pos.m_lineno),
              cereal::make_nvp("columno", m_pos.m_columno));
  }

  AST_VISITOR_VISITABLE_PURE_ACCEPT(visitor::NodeVisitor);

  virtual ~NodePosition() = default;
};
} // namespace ast::node::node_traits

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::node_traits, NodePosition);

#endif // CROW_CROW_AST_NODE_NODE_TRAITS_NODE_POSITION_HPP
