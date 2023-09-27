#ifndef CROW_BACKEND_LLVM_BACKEND_LLVM_BACKEND_HPP
#define CROW_BACKEND_LLVM_BACKEND_LLVM_BACKEND_HPP

// STL Includes:
#include <filesystem>

// Local Includes:
#include "prologue_generator.hpp"


namespace backend::llvm_backend {
// Using statements:
using namespace ast;

// Namespace aliases:
namespace fs = std::filesystem;

// Classes:
class LlvmBackend : public ast::visitor::NodeVisitor {
  private:
  ContextPtr m_context;
  IrBuilderPtr m_builder;
  ModulePtr m_module;

  PrologueGenerator m_pgen;

  public:
  LlvmBackend();

  // Control:
  auto visit(node::control::If* t_if) -> void override;
  auto visit(node::control::Loop* t_loop) -> void override;
  auto visit(node::control::Continue* t_continue) -> void override;
  auto visit(node::control::Break* t_break) -> void override;
  auto visit(node::control::Return* t_return) -> void override;

  // Function:
  auto visit(node::functions::Function* t_fn) -> void override;
  auto visit(node::functions::FunctionCall* t_fn_call) -> void override;
  auto visit(node::functions::ReturnType* t_rt) -> void override;

  // Lvalue:
  auto visit(node::lvalue::Const* t_const) -> void override;
  auto visit(node::lvalue::Let* t_let) -> void override;
  auto visit(node::lvalue::Variable* t_var) -> void override;

  // Operators:
  auto visit(node::operators::Arithmetic* t_arithmetic) -> void override;
  auto visit(node::operators::Assignment* t_assignment) -> void override;
  auto visit(node::operators::Comparison* t_comparison) -> void override;

  auto visit(node::operators::Increment* t_inc) -> void override;
  auto visit(node::operators::Decrement* t_dec) -> void override;

  auto visit(node::operators::UnaryPrefix* t_unary_prefix) -> void override;

  // Logical:
  auto visit(node::operators::Not* t_not) -> void override;
  auto visit(node::operators::And* t_and) -> void override;
  auto visit(node::operators::Or* t_or) -> void override;

  auto visit(node::operators::Ternary* t_ternary) -> void override;

  // Packaging:
  auto visit(node::packaging::Import* t_import) -> void override;
  auto visit(node::packaging::ModuleDecl* t_mod) -> void override;

  // Rvalue:
  auto visit(node::rvalue::Float* t_float) -> void override;
  auto visit(node::rvalue::Integer* t_int) -> void override;
  auto visit(node::rvalue::String* t_str) -> void override;
  auto visit(node::rvalue::Boolean* t_bool) -> void override;

  // Typing:
  auto visit(ast::node::typing::MethodDecl* t_md) -> void override;
  auto visit(ast::node::typing::Interface* t_ifc) -> void override;
  auto visit(ast::node::typing::MemberDecl* t_md) -> void override;
  auto visit(ast::node::typing::Struct* t_struct) -> void override;
  auto visit(ast::node::typing::Impl* t_impl) -> void override;
  auto visit(ast::node::typing::DotExpr* t_dot_expr) -> void override;

  // Util:
  auto configure_target() -> void;
  auto codegen(ast::node::NodePtr t_ast) -> void;
  auto dump_ir(std::ostream& t_os) -> void;
  auto compile(fs::path t_path) -> void;

  ~LlvmBackend() override = default;
};
} // namespace backend::llvm_backend

#endif // CROW_BACKEND_LLVM_BACKEND_LLVM_BACKEND_HPP
