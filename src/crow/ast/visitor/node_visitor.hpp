#ifndef CROW_CROW_AST_VISITOR_NODE_VISITOR_HPP
#define CROW_CROW_AST_VISITOR_NODE_VISITOR_HPP

// Relative AST Includes:
#include "../node/fdecl.hpp"

// Local Includes:
#include "visitable.hpp"


// Macros:
#define AST_VISITOR_STUB(t_class, t_type)                  \
  /* NOLINTBEGIN */                                        \
  auto t_class::visit([[maybe_unused]] t_type* t_ptr)->Any \
  {                                                        \
    return {};                                             \
  }

/* NOLINTBEGIN */
namespace ast::visitor {
// Using statements:
using node::NodePtr;

// Classes:
/*!
 * Implementation of the Visitor design pattern for Nodes
 * This creates a recursive dependency on the different kind of nodes
 * So all nodes need to be forward declared in this header
 */
class NodeVisitor {
  protected:
  virtual auto traverse(NodePtr t_ast) -> Any;

  public:
  NodeVisitor() = default;

  // Control:
  virtual auto visit(node::control::If* t_if) -> Any;
  virtual auto visit(node::control::Loop* t_loop) -> Any;
  virtual auto visit(node::control::Continue* t_continue) -> Any;
  virtual auto visit(node::control::Break* t_break) -> Any;
  virtual auto visit(node::control::Return* t_return) -> Any;

  // Function:
  virtual auto visit(node::function::Parameter* t_param) -> Any;
  virtual auto visit(node::function::Function* t_fn) -> Any;
  virtual auto visit(node::function::Call* t_fn_call) -> Any;
  virtual auto visit(node::function::ReturnType* t_rt) -> Any;

  // Lvalue:
  virtual auto visit(node::lvalue::Let* t_let) -> Any;
  virtual auto visit(node::lvalue::Var* t_var) -> Any;
  virtual auto visit(node::lvalue::Variable* t_var) -> Any;

  // Operators:
  virtual auto visit(node::operators::Arithmetic* t_arith) -> Any;
  virtual auto visit(node::operators::Assignment* t_assign) -> Any;
  virtual auto visit(node::operators::Comparison* t_comp) -> Any;

  virtual auto visit(node::operators::Increment* t_inc) -> Any;
  virtual auto visit(node::operators::Decrement* t_dec) -> Any;

  virtual auto visit(node::operators::UnaryPrefix* t_up) -> Any;

  // Logical:
  virtual auto visit(node::operators::Not* t_not) -> Any;
  virtual auto visit(node::operators::And* t_and) -> Any;
  virtual auto visit(node::operators::Or* t_or) -> Any;

  virtual auto visit(node::operators::Ternary* t_ternary) -> Any;

  // Packaging:
  virtual auto visit(node::packaging::Import* t_import) -> Any;
  virtual auto visit(node::packaging::ModuleDecl* t_mod) -> Any;

  // Rvalue:
  virtual auto visit(node::rvalue::Float* t_float) -> Any;
  virtual auto visit(node::rvalue::Integer* t_int) -> Any;
  virtual auto visit(node::rvalue::String* t_str) -> Any;
  virtual auto visit(node::rvalue::Boolean* t_bool) -> Any;

  // Typing:
  virtual auto visit(node::typing::MethodDecl* t_md) -> Any;
  virtual auto visit(node::typing::Interface* t_ifc) -> Any;
  virtual auto visit(node::typing::MemberDecl* t_md) -> Any;
  virtual auto visit(node::typing::Struct* t_struct) -> Any;
  virtual auto visit(node::typing::Impl* t_impl) -> Any;
  virtual auto visit(node::typing::DotExpr* t_dot_expr) -> Any;

  // Misc:
  virtual auto visit(node::List* t_list) -> Any;
  virtual auto visit(node::Nil* t_nil) -> Any;

  virtual auto visit(node::NodeInterface* t_ptr) -> Any;

  virtual ~NodeVisitor() = default;
};
} // namespace ast::visitor

/* NOLINTEND */

#endif // CROW_CROW_AST_VISITOR_NODE_VISITOR_HPP
