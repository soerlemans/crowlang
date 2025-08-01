#ifndef CROW_CROW_CODEGEN_LLVM_BACKEND_LLVM_BACKEND_HPP
#define CROW_CROW_CODEGEN_LLVM_BACKEND_LLVM_BACKEND_HPP

// STL Includes:
#include <filesystem>
#include <memory>

// Library Includes:
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

// Absolute Includes:
#include "crow/ast/visitor/node_visitor.hpp"
#include "crow/codegen/backend_interface.hpp"

/*!
 * @file
 *
 * FIXME: As of now the @ref LlvmBackend is in a half broken state.
 * It should be properly implemented and fixed one day.
 */


namespace codegen::llvm_backend {
// Using statements:
using namespace ast;

// Using Declarations:
using ast::node::NodePtr;
using ast::visitor::Any;
using ast::visitor::NodeVisitor;
using std::filesystem::path;

// Aliases:
using ContextPtr = std::shared_ptr<llvm::LLVMContext>;
using IrBuilderPtr = std::shared_ptr<llvm::IRBuilder<>>;
using ModulePtr = std::shared_ptr<llvm::Module>;

// Namespace aliases:
namespace fs = std::filesystem;

// Classes:
class LlvmBackend : public BackendInterface, public NodeVisitor {
  private:
  ContextPtr m_context;
  IrBuilderPtr m_builder;
  ModulePtr m_module;

  protected:
  auto get_value(NodePtr t_ptr) -> llvm::Value*;

  public:
  LlvmBackend();

  // Control:
  auto visit(node::control::If* t_if) -> Any override;
  auto visit(node::control::Loop* t_loop) -> Any override;
  auto visit(node::control::Continue* t_continue) -> Any override;
  auto visit(node::control::Break* t_break) -> Any override;
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

  auto visit(node::operators::Ternary* t_ternary) -> Any override;

  // Packaging:
  auto visit(node::packaging::Import* t_import) -> Any override;
  auto visit(node::packaging::ModuleDecl* t_mod) -> Any override;

  // Rvalue:
  auto visit(node::rvalue::Float* t_float) -> Any override;
  auto visit(node::rvalue::Integer* t_int) -> Any override;
  auto visit(node::rvalue::String* t_str) -> Any override;
  auto visit(node::rvalue::Boolean* t_bool) -> Any override;

  // Typing:
  auto visit(ast::node::typing::MethodDecl* t_md) -> Any override;
  auto visit(ast::node::typing::Interface* t_ifc) -> Any override;
  auto visit(ast::node::typing::MemberDecl* t_md) -> Any override;
  auto visit(ast::node::typing::Struct* t_struct) -> Any override;
  auto visit(ast::node::typing::Impl* t_impl) -> Any override;
  auto visit(ast::node::typing::DotExpr* t_dot_expr) -> Any override;

  // Util:
  auto configure_target() -> void;
  auto dump_ir(std::ostream& t_os) -> void;

  //! LLVM backend as of writing supports no interop.
  auto register_interop_backend([[maybe_unused]] InteropBackendType t_type)
    -> void override {};
  auto compile(CompileParams& t_params) -> void override;

  virtual ~LlvmBackend() = default;
};
} // namespace codegen::llvm_backend

#endif // CROW_CROW_CODEGEN_LLVM_BACKEND_LLVM_BACKEND_HPP
