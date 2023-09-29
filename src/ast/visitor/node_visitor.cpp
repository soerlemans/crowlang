#include "node_visitor.hpp"

// STL Includes:
#include <cassert>

// Includes:
#include "../../debug/log.hpp"
#include "../node/include.hpp"


// Macros:
#define assert_msg(t_msg, t_expr) assert(((void)t_msg, t_expr))

// Using statements:
using namespace ast::visitor;

NODE_USING_ALL_NAMESPACES()

#define STUB(t_type)                                                     \
  auto NodeVisitor::visit([[maybe_unused]] t_type* t_ptr)->Any           \
  {                                                                      \
    DBG_WARNING("NodeVisitor::visit(", #t_type, "*) is not overriden!"); \
                                                                         \
    return {};                                                           \
  }

STUB(If)
STUB(Loop)
STUB(Continue)
STUB(Break)
STUB(Return)
STUB(Function)
STUB(FunctionCall)
STUB(ReturnType)
STUB(Const)
STUB(Let)
STUB(Variable)
STUB(Arithmetic)
STUB(Assignment)
STUB(Comparison)
STUB(Increment)
STUB(Decrement)
STUB(UnaryPrefix)
STUB(Not)
STUB(And)
STUB(Or)
STUB(Ternary)
STUB(Import)
STUB(ModuleDecl)
STUB(Float)
STUB(Integer)
STUB(String)
STUB(Boolean)
STUB(MethodDecl)
STUB(Interface)
STUB(MemberDecl)
STUB(Struct)
STUB(Impl)
STUB(DotExpr)

// Misc:
auto NodeVisitor::visit(List* t_list) -> Any
{
  for(NodePtr& node : *t_list) {
    node->accept(this);
  }

  return {};
}

auto NodeVisitor::visit([[maybe_unused]] Nil* t_nil) -> Any
{
  DBG_INFO("Visited a Nil node");

  return {};
}

//! This catches the error case where a node does not have its own method
auto NodeVisitor::visit(NodeInterface* t_ptr) -> Any
{
  assert_msg("NodeVisitor: Received a NodeInterface*", t_ptr);

  return {};
}

//! Traverse all nodes neatly
auto NodeVisitor::traverse(NodePtr t_ast) -> Any
{
  t_ast->accept(this);

  return {};
}
