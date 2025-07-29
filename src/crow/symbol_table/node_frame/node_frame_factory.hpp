#ifndef CROW_CROW_SYMBOL_TABLE_NODE_FRAME_NODE_FRAME_FACTORY_HPP
#define CROW_CROW_SYMBOL_TABLE_NODE_FRAME_NODE_FRAME_FACTORY_HPP

// Absolute includes:
#include "crow/ast/visitor/node_visitor.hpp"
#include "crow/symbol_table/symbol_tree/symbol_tree_factory.hpp"

// Local Includes:
#include "symbol_node_frame.hpp"

namespace symbol_table::node_frame {
// Using Declarations:
using ast::visitor::NodeVisitor;

// Classes:
class NodeFrameFactory : public NodeVisitor {
  private:
  public:
  NodeFrameFactory() = default;

  virtual ~NodeFrameFactory() = default;
};

} // namespace symbol_table::node_frame

#endif // CROW_CROW_SYMBOL_TABLE_NODE_FRAME_NODE_FRAME_FACTORY_HPP
