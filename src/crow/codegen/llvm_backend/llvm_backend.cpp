#include "llvm_backend.hpp"

// STL Includes:
#include <iostream>
#include <optional>
#include <vector>

// Library Includes:
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Verifier.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Support/CodeGen.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Target/TargetMachine.h>

// Absolute Includes:
#include "crow/debug/log.hpp"
#include "crow/mir/mir.hpp"
#include "lib/filesystem.hpp"
#include "lib/stdtypes.hpp"

// Local Includes:
#include "type2llvm.hpp"

namespace codegen::llvm_backend {
// Methods:
LlvmBackend::LlvmBackend()
  : m_context{std::make_shared<llvm::LLVMContext>()},
    m_builder{std::make_shared<llvm::IRBuilder<>>(*m_context)},
    m_module{std::make_shared<llvm::Module>("Module", *m_context)}
{}

auto LlvmBackend::on_module(ModulePtr& t_module) -> void
{
  for(FunctionPtr& fn : t_module->m_functions) {
    on_function(fn);
  }
}

auto LlvmBackend::on_function(FunctionPtr& t_fn) -> void
{
  const auto fn_name{t_fn->m_name};

  auto params{std::vector<llvm::Type*>()};

  // FIXME: We only support native types right now.
  auto return_type{t_fn->m_return_type};
  const auto opt{return_type.native_type()};
  if(!opt) {
    DBG_ERROR("Cancelling function LLVM IR generation, cause return type is "
              "note resolvalbe to native type.");
    return;
  }
  const auto native_type{opt.value()};
  auto* llvm_return_type{native_type2llvm(m_context, native_type)};

  auto* fn_type{llvm::FunctionType::get(llvm_return_type, params, false)};

  auto* fn{llvm::Function::Create(fn_type, llvm::Function::ExternalLinkage,
                                  fn_name, m_module.get())};

  auto* main_block{llvm::BasicBlock::Create(*m_context, "main", fn)};
  m_builder->SetInsertPoint(main_block);

  // Codegen for the body
  for(BasicBlock& block : t_fn->m_blocks) {
    on_block(block);
  }

  llvm::verifyFunction(*fn);
}

auto LlvmBackend::on_block(BasicBlock& t_block) -> void
{
  for(Instruction& instr : t_block.m_instructions) {
    on_instruction(instr);
  }
}

auto LlvmBackend::on_instruction(Instruction& t_instr) -> void
{
  using mir::Opcode;

  const auto& [id, opcode, operands, result, comment] = t_instr;

  switch(opcode) {
    case Opcode::CONST_F32:
      break;
    case Opcode::CONST_F64:
      break;
    case Opcode::CONST_INT:
      break;
    case Opcode::CONST_STRING:
      break;
    case Opcode::CONST_BOOL:
      break;
    case Opcode::IADD:
      break;
    case Opcode::ISUB:
      break;
    case Opcode::IMUL:
      break;
    case Opcode::IDIV:
      break;
    case Opcode::IMOD:
      break;
    case Opcode::INEG:
      break;
    case Opcode::ICMP_LT:
      break;
    case Opcode::ICMP_LTE:
      break;
    case Opcode::ICMP_EQ:
      break;
    case Opcode::ICMP_NQ:
      break;
    case Opcode::ICMP_GT:
      break;
    case Opcode::ICMP_GTE:
      break;
    case Opcode::FADD:
      break;
    case Opcode::FSUB:
      break;
    case Opcode::FMUL:
      break;
    case Opcode::FDIV:
      break;
    case Opcode::FNEG:
      break;
    case Opcode::FCMP_LT:
      break;
    case Opcode::FCMP_LTE:
      break;
    case Opcode::FCMP_EQ:
      break;
    case Opcode::FCMP_NQ:
      break;
    case Opcode::FCMP_GT:
      break;
    case Opcode::FCMP_GTE:
      break;
    case Opcode::INIT:
      break;
    case Opcode::UPDATE:
      break;
    case Opcode::LOAD:
      break;
    case Opcode::STORE:
      break;
    case Opcode::ALLOCA:
      break;
    case Opcode::LEA:
      break;
    case Opcode::COND_JUMP:
      break;
    case Opcode::JUMP:
      break;
    case Opcode::CONTINUE:
      break;
    case Opcode::BREAK:
      break;
    case Opcode::RETURN:
      break;
    case Opcode::PHI:
      break;
    case Opcode::LOOP:
      break;
    case Opcode::CALL:
      break;
    case Opcode::NOP:
      break;

    default:
      // For now we log as we are still implementing the IR.
      DBG_ERROR("Unhandled opcode: ", opcode);
      break;
  }
}

auto LlvmBackend::initialize_target() -> void
{
  const auto target{llvm::sys::getDefaultTargetTriple()};

  m_module->setTargetTriple(target);

  // Initialize all target stuff:
  llvm::InitializeAllTargetInfos();
  llvm::InitializeAllTargets();
  llvm::InitializeAllTargetMCs();
  llvm::InitializeAllAsmParsers();
  llvm::InitializeAllAsmPrinters();
}

auto LlvmBackend::dump_ir(std::ostream& t_os) -> void
{
  std::string str;
  llvm::raw_string_ostream oss(str);

  m_module->print(oss, nullptr);

  t_os << str;
}

//! FIXME: For now we do nothing with the @ref SymbolTable
auto LlvmBackend::compile(CompileParams& t_params) -> void
{
  using namespace llvm;
  using namespace llvm::sys::fs;

  using mir::mir_pass::MirPassParams;

  const auto& [ast, mir_module, build_dir, source_path] = t_params;

  fs::path stem{source_path.stem()};
  const fs::path tmp_src{build_dir / stem.concat(".ll")};

  // Log filepath's:
  DBG_INFO("build_dir: ", build_dir);
  DBG_INFO("tmp_src: ", tmp_src);

  // Initialize the LLVM target.
  initialize_target();

  // Obtain filehandle to destination file
  const auto filename{tmp_src.c_str()};
  std::error_code err_code{};
  raw_fd_ostream dest{filename, err_code, sys::fs::OF_None};

  if(err_code) {
    errs() << "Could not open file: " << err_code.message();
    return;
  }

  // Resolve target:
  const auto target_str{m_module->getTargetTriple()};
  DBG_INFO("LLVM target: ", target_str);

  std::string err{};
  auto target{TargetRegistry::lookupTarget(target_str, err)};
  if(!target) {
    errs() << err << '\n';

    return; // TODO: Fix
  }

  // Set target machine:
  const auto cpu{"generic"};
  const auto features{""};

  TargetOptions opt{};
  std::optional<Reloc::Model> reloc_model{};
  auto target_machine{
    target->createTargetMachine(target_str, cpu, features, opt, reloc_model)};

  // Write object file:
  legacy::PassManager pass{};
  const auto fype{CGFT_ObjectFile};
  if(target_machine->addPassesToEmitFile(pass, dest, nullptr, fype)) {
    errs() << "target_machine can't emit a file of this type";
    return; // TODO: Fix
  }

  // Traverse ast to generate LLVM IR:
  MirPassParams params{mir_module};
  run_pass(params);

  dump_ir(std::cout);

  if(llvm::verifyModule(*m_module, &llvm::errs())) {
    llvm::errs() << "Error: The module is invalid!\n";
    return; // Exit or handle the error appropriately
  }

  //
  pass.run(*m_module);
  dest.flush();

  // Close so that the permissions can be set
  dest.close();

  // Make object file executable:
  const perms permissions{others_write | all_read | all_exe};
  err_code = setPermissions(tmp_src.c_str(), permissions);

  errs() << err_code.message() << " Done...\n";

  if(err_code) {
    errs() << "Could not change file permissions: " << err_code.message();
    return;
  }
}
} // namespace codegen::llvm_backend
