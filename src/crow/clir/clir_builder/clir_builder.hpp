#ifndef CROW_CROW_CLIR_CLIR_BUILDER_CLIR_BUILDER_HPP
#define CROW_CROW_CLIR_CLIR_BUILDER_CLIR_BUILDER_HPP

// Absolute Includes:
#include "crow/ast/visitor/node_visitor.hpp"

namespace clir::clir_builder {
// Using:
using ast::node::NodePtr;
using ast::visitor::Any;
using ast::visitor::NodeVisitor;

// Classes:
/*!
 */
class ClirBuilder : public NodeVisitor {
  public:
  ClirBuilder() = default;

  // Control:
  virtual auto visit(ast::node::control::If* t_if) -> Any;
  virtual auto visit(ast::node::control::Loop* t_loop) -> Any;
  virtual auto visit(ast::node::control::Continue* t_continue) -> Any;
  virtual auto visit(ast::node::control::Break* t_break) -> Any;
  virtual auto visit(ast::node::control::Defer* t_defer) -> Any;
  virtual auto visit(ast::node::control::Return* t_return) -> Any;

  // Function:
  virtual auto visit(ast::node::function::Parameter* t_param) -> Any;
  virtual auto visit(ast::node::function::Function* t_fn) -> Any;
  virtual auto visit(ast::node::function::Call* t_fn_call) -> Any;
  virtual auto visit(ast::node::function::ReturnType* t_rt) -> Any;

  // Lvalue:
  virtual auto visit(ast::node::lvalue::Let* t_let) -> Any;
  virtual auto visit(ast::node::lvalue::Var* t_var) -> Any;
  virtual auto visit(ast::node::lvalue::Variable* t_var) -> Any;

  // Operators:
  virtual auto visit(ast::node::operators::Arithmetic* t_arith) -> Any;
  virtual auto visit(ast::node::operators::Assignment* t_assign) -> Any;
  virtual auto visit(ast::node::operators::Comparison* t_comp) -> Any;

  virtual auto visit(ast::node::operators::Increment* t_inc) -> Any;
  virtual auto visit(ast::node::operators::Decrement* t_dec) -> Any;

  virtual auto visit(ast::node::operators::UnaryPrefix* t_up) -> Any;

  // Logical:
  virtual auto visit(ast::node::operators::Not* t_not) -> Any;
  virtual auto visit(ast::node::operators::And* t_and) -> Any;
  virtual auto visit(ast::node::operators::Or* t_or) -> Any;

  virtual auto visit(ast::node::operators::Ternary* t_ternary) -> Any;

  // Packaging:
  virtual auto visit(ast::node::packaging::Import* t_import) -> Any;
  virtual auto visit(ast::node::packaging::ModuleDecl* t_mod) -> Any;

  // Rvalue:
  virtual auto visit(ast::node::rvalue::Float* t_float) -> Any;
  virtual auto visit(ast::node::rvalue::Integer* t_int) -> Any;
  virtual auto visit(ast::node::rvalue::String* t_str) -> Any;
  virtual auto visit(ast::node::rvalue::Boolean* t_bool) -> Any;

  // Typing:
  virtual auto visit(ast::node::typing::MethodDecl* t_md) -> Any;
  virtual auto visit(ast::node::typing::Interface* t_ifc) -> Any;
  virtual auto visit(ast::node::typing::MemberDecl* t_md) -> Any;
  virtual auto visit(ast::node::typing::Struct* t_struct) -> Any;
  virtual auto visit(ast::node::typing::Impl* t_impl) -> Any;
  virtual auto visit(ast::node::typing::DotExpr* t_dot_expr) -> Any;

  // Misc:
  virtual auto visit(ast::node::List* t_list) -> Any;
  virtual auto visit(ast::node::Nil* t_nil) -> Any;

  virtual auto visit(ast::node::NodeInterface* t_ptr) -> Any;

  virtual ~ClirBuilder() = default;
};


} // namespace clir::clir_builder

#endif // CROW_CROW_CLIR_CLIR_BUILDER_CLIR_BUILDER_HPP
