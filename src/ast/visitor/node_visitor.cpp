#include "node_visitor.hpp"

// Includes:
#include "../node/node_interface.hpp"


using namespace ast::visitor;
using namespace ast::node;

auto NodeVisitor::visit(NodeInterface* t_node) -> void
{
  t_node->accept(this);
}
