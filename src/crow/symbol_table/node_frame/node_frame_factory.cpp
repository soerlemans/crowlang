#ifndef SYMBOL_NODE_FRAME_FACTORY_HPP
#define SYMBOL_NODE_FRAME_FACTORY_HPP

// Local Includes:
#include "symbol_node_frame.hpp"

namespace symbol_table::node_frame {
class NodeFrameFactory {
  private:
  public:
  NodeFrameFactory() = default;

  virtual ~NodeFrameFactory() = default;
};

} // namespace symbol_table::node_frame

#endif // SYMBOL_NODE_FRAME_FACTORY_HPP
