#include "node_visitor.hpp"

// STL Includes:
#include <cassert>

// Absolute Includes:
#include "crow/ast/node/include_nodes.hpp"
#include "crow/debug/log.hpp"
#include "lib/stdexcept/stdexcept.hpp"


// Macros:
// TODO: Place somewhere appropriate
#define assert_msg(t_msg, t_expr) assert(((void)t_msg, t_expr))

#define STUB(t_type)                                              \
  auto NodeVisitor::visit([[maybe_unused]] t_type* t_ptr) -> Any  \
  {                                                               \
    DBG_CRITICAL("Method for type ", #t_type, " not overriden!"); \
                                                                  \
    return {};                                                    \
  }

namespace ast::visitor {
// Using statements:
NODE_USING_ALL_NAMESPACES()

// Methods:
//! Traverse all nodes neatly
auto NodeVisitor::traverse(NodePtr t_node) -> Any
{
  Any any{};

  // Throw on nullptr.
  if(!t_node) {
    using lib::stdexcept::throw_unexpected_nullptr;

    throw_unexpected_nullptr("Cant traverse a nullptr.");
  }

  // Kick off the traversal.
  any = t_node->accept(this);

  return any;
}

// Stubs:
STUB(If)
STUB(Loop)
STUB(Continue)
STUB(Break)
STUB(Defer)
STUB(Return)
STUB(Parameter)
STUB(Function)
STUB(Call)
STUB(ReturnType)
STUB(Let)
STUB(Var)
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
    traverse(node);
  }

  return {};
}

auto NodeVisitor::visit([[maybe_unused]] Nil* t_nil) -> Any
{
  DBG_INFO("Visited a Nil node");

  return {};
}

//! This catches the error case where a node does not have its own method
auto NodeVisitor::visit([[maybe_unused]] NodeInterface* t_ptr) -> Any
{
  assert_msg("NodeVisitor: Received a NodeInterface*", t_ptr);

  return {};
}
} // namespace ast::visitor
