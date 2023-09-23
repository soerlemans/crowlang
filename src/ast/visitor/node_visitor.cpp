#include "node_visitor.hpp"

// STL Includes:
#include <cassert>

// Includes:
#include "../node/node_interface.hpp"


// Macros:
#define assert_msg(t_msg, t_expr) assert(((void)t_msg, t_expr))

using namespace ast::visitor;
using namespace ast::node;

//! This catches the error case where an oaolvred is not defined for a
auto NodeVisitor::visit(NodeInterface* t_ptr) -> void
{
  assert_msg("NodeVisitor: Received a NodeInterface*", t_ptr);
}

auto NodeVisitor::traverse(NodePtr t_ast) -> void
{
  t_ast->accept(this);
}
