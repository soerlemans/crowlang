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
#include "crow/mir/mir_pass/mir_pass.hpp"

/*!
 * @file
 *
 * FIXME: As of now the @ref LlvmBackend is in a half broken state.
 * It should be properly implemented and fixed one day.
 */


namespace codegen::llvm_backend {
// Aliases:
namespace fs = std::filesystem;

using mir::mir_pass::MirPass;

using ContextPtr = std::shared_ptr<llvm::LLVMContext>;
using IrBuilderPtr = std::shared_ptr<llvm::IRBuilder<>>;
using ModulePtr = std::shared_ptr<llvm::Module>;

// Classes:
class LlvmBackend : public MirPass, public BackendInterface {
  private:
  ContextPtr m_context;
  IrBuilderPtr m_builder;
  ModulePtr m_module;

  public:
  LlvmBackend();

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
