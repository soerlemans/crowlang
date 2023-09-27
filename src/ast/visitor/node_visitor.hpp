#ifndef CROW_AST_VISITOR_NODE_VISITOR_HPP
#define CROW_AST_VISITOR_NODE_VISITOR_HPP

// Includes:
#include "../node/fdecl.hpp"


namespace ast::visitor {
// Classes:
/*! Implementation of the Visitor design pattern for Nodes
 * This creates a recursive dependency on the different kind of nodes
 * So all nodes need to be forward declared in this header
 */
class NodeVisitor {
  private:
  public:
  NodeVisitor() = default;

  // Control:
  virtual auto visit(node::control::If* t_if) -> void;
  virtual auto visit(node::control::Loop* t_loop) -> void;
  virtual auto visit(node::control::Continue* t_continue) -> void;
  virtual auto visit(node::control::Break* t_break) -> void;
  virtual auto visit(node::control::Return* t_return) -> void;

  // Function:
  virtual auto visit(node::functions::Function* t_fn) -> void;
  virtual auto visit(node::functions::FunctionCall* t_fn_call) -> void;
  virtual auto visit(node::functions::ReturnType* t_rt) -> void;

  // Lvalue:
  virtual auto visit(node::lvalue::Const* t_const) -> void;
  virtual auto visit(node::lvalue::Let* t_let) -> void;
  virtual auto visit(node::lvalue::Variable* t_var) -> void;

  // Operators:
  virtual auto visit(node::operators::Arithmetic* t_arithmetic) -> void;
  virtual auto visit(node::operators::Assignment* t_assignment) -> void;
  virtual auto visit(node::operators::Comparison* t_comparison) -> void;

  virtual auto visit(node::operators::Increment* t_increment) -> void;
  virtual auto visit(node::operators::Decrement* t_decrement) -> void;

  virtual auto visit(node::operators::UnaryPrefix* t_unary_prefix) -> void;

  // Logical:
  virtual auto visit(node::operators::Not* t_not) -> void;
  virtual auto visit(node::operators::And* t_and) -> void;
  virtual auto visit(node::operators::Or* t_or) -> void;

  virtual auto visit(node::operators::Ternary* t_ternary) -> void;

  // Packaging:
  virtual auto visit(node::packaging::Import* t_import) -> void;
  virtual auto visit(node::packaging::ModuleDecl* t_mod) -> void;

  // Rvalue:
  virtual auto visit(node::rvalue::Float* t_float) -> void;
  virtual auto visit(node::rvalue::Integer* t_int) -> void;
  virtual auto visit(node::rvalue::String* t_str) -> void;
  virtual auto visit(node::rvalue::Boolean* t_bool) -> void;

  // Typing:
  virtual auto visit(node::typing::MethodDecl* t_md) -> void;
  virtual auto visit(node::typing::Interface* t_ifc) -> void;
  virtual auto visit(node::typing::MemberDecl* t_md) -> void;
  virtual auto visit(node::typing::Struct* t_struct) -> void;
  virtual auto visit(node::typing::DefBlock* t_db) -> void;
  virtual auto visit(node::typing::DotExpr* t_dot_expr) -> void;

  // Misc:
  virtual auto visit(node::List* t_list) -> void;
  virtual auto visit(node::Nil* t_nil) -> void;

  virtual auto visit(node::NodeInterface* t_ptr) -> void;
  virtual auto traverse(node::NodePtr t_ast) -> void;

  virtual ~NodeVisitor() = default;
};
} // namespace ast::visitor

#endif // CROW_AST_VISITOR_NODE_VISITOR_HPP
