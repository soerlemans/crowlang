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
#include "crow/mir/mir.hpp"
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

using mir::BasicBlock;
using mir::FunctionPtr;
using mir::Instruction;
using mir::ModulePtr;
using mir::mir_pass::MirPass;

using LlvmContextPtr = std::shared_ptr<llvm::LLVMContext>;
using LlvmIrBuilderPtr = std::shared_ptr<llvm::IRBuilder<>>;
using LlvmModulePtr = std::shared_ptr<llvm::Module>;

// Classes:
class LlvmBackend : public MirPass, public BackendInterface {
  private:
  LlvmContextPtr m_context;
  LlvmIrBuilderPtr m_builder;
  LlvmModulePtr m_module;

  public:
  LlvmBackend();

  auto on_module(ModulePtr& t_module) -> void override;
  auto on_function(FunctionPtr& t_fn) -> void override;
  auto on_block(BasicBlock& t_block) -> void override;
  auto on_instruction(Instruction& t_instr) -> void override;

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
