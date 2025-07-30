#ifndef CROW_CROW_SYMBOL_TABLE_NODE_FRAME_NODE_FRAME_FACTORY_HPP
#define CROW_CROW_SYMBOL_TABLE_NODE_FRAME_NODE_FRAME_FACTORY_HPP

// Absolute includes:
#include "crow/ast/node/include.hpp"
#include "crow/ast/visitor/node_visitor.hpp"
#include "crow/symbol_table/symbol_table.hpp"
#include "crow/symbol_table/symbol_tree/symbol_tree_factory.hpp"

namespace symbol_table::node_frame {
// Using Declarations:
using ast::node::NodeInterface;
using ast::node::NodePtr;
using ast::visitor::Any;
using ast::visitor::NodeVisitor;
using symbol_register::SymbolRegister;
using symbol_register::SymbolRegisterPtr;
using symbol_tree::SymbolTreeFactory;
using symbol_tree::SymbolTreePtr;
using symbol_tree::SymbolTreeResult;

// Aliases:
namespace node = ast::node;

/*!
 * Different specializiations of @ref SymbolTable are usually, constructed.
 * From the AST, this is a frame/view which maps the @ref SymbolTree.
 * To accompanying AST nodes.
 */
using NodeFrame = SymbolTable<NodeInterface>;
using NodeFramePtr = SymbolTablePtr<NodeInterface>;

// Classes:
class NodeFrameFactory : public NodeVisitor {
  private:
  SymbolTreeFactory m_tree_factory;
  SymbolRegister<NodeInterface> m_register;

  public:
  NodeFrameFactory();

  // Control:
  auto visit(node::control::If* t_if) -> Any override;
  auto visit(node::control::Loop* t_loop) -> Any override;
  auto visit(node::control::Continue* t_continue) -> Any override;
  auto visit(node::control::Break* t_break) -> Any override;
  auto visit(node::control::Defer* t_defer) -> Any override;
  auto visit(node::control::Return* t_return) -> Any override;

  // Function:
  auto visit(node::function::Parameter* t_param) -> Any override;
  auto visit(node::function::Function* t_fn) -> Any override;
  auto visit(node::function::Call* t_fn_call) -> Any override;
  auto visit(node::function::ReturnType* t_rt) -> Any override;

  // Lvalue:
  auto visit(node::lvalue::Let* t_let) -> Any override;
  auto visit(node::lvalue::Var* t_var) -> Any override;
  auto visit(node::lvalue::Variable* t_var) -> Any override;

  // Operators:
  auto visit(node::operators::Arithmetic* t_arith) -> Any override;
  auto visit(node::operators::Assignment* t_assign) -> Any override;
  auto visit(node::operators::Comparison* t_comp) -> Any override;

  auto visit(node::operators::Increment* t_inc) -> Any override;
  auto visit(node::operators::Decrement* t_dec) -> Any override;

  auto visit(node::operators::UnaryPrefix* t_up) -> Any override;

  // Logical:
  auto visit(node::operators::Not* t_not) -> Any override;
  auto visit(node::operators::And* t_and) -> Any override;
  auto visit(node::operators::Or* t_or) -> Any override;

  // auto visit(node::operators::Ternary* t_ternary) -> Any override;

  // Packaging:
  auto visit(node::packaging::Import* t_import) -> Any override;
  auto visit(node::packaging::ModuleDecl* t_mod) -> Any override;

  // Rvalue:
  auto visit(node::rvalue::Float* t_float) -> Any override;
  auto visit(node::rvalue::Integer* t_int) -> Any override;
  auto visit(node::rvalue::String* t_str) -> Any override;
  auto visit(node::rvalue::Boolean* t_bool) -> Any override;

  // Typing:
  auto visit(node::typing::MethodDecl* t_md) -> Any override;
  auto visit(node::typing::Interface* t_ifc) -> Any override;
  auto visit(node::typing::MemberDecl* t_md) -> Any override;
  auto visit(node::typing::Struct* t_struct) -> Any override;
  auto visit(node::typing::Impl* t_impl) -> Any override;
  auto visit(node::typing::DotExpr* t_dot_expr) -> Any override;

  // Misc:
  virtual auto visit(node::List* t_list) -> Any override;

  auto push_scope() -> void;
  auto pop_scope() -> void;

  auto construct_frame(NodePtr t_ast) -> NodeFramePtr;

  virtual ~NodeFrameFactory() = default;
};
} // namespace symbol_table::node_frame

#endif // CROW_CROW_SYMBOL_TABLE_NODE_FRAME_NODE_FRAME_FACTORY_HPP
