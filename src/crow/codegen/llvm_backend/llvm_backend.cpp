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
#include "crow/ast/node/include_nodes.hpp"
#include "crow/debug/log.hpp"
#include "lib/filesystem.hpp"
#include "lib/stdtypes.hpp"

namespace codegen::llvm_backend {
// Using:
using llvm::Value;

NODE_USING_ALL_NAMESPACES()

// Methods:
LlvmBackend::LlvmBackend()
  : m_context{std::make_shared<llvm::LLVMContext>()},
    m_builder{std::make_shared<llvm::IRBuilder<>>(*m_context)},
    m_module{std::make_shared<llvm::Module>("Module", *m_context)}
{}

auto LlvmBackend::configure_target() -> void
{
  const auto target{llvm::sys::getDefaultTargetTriple()};

  m_module->setTargetTriple(target);
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

  const auto& [ast, mir, build_dir, source_path] = t_params;

  configure_target();

  fs::path stem{source_path.stem()};
  const fs::path tmp_src{build_dir / stem.concat(".ll")};

  // Log filepath's:
  DBG_INFO("build_dir: ", build_dir);
  DBG_INFO("tmp_src: ", tmp_src);

  // Initialize all target stuff:
  InitializeAllTargetInfos();
  InitializeAllTargets();
  InitializeAllTargetMCs();
  InitializeAllAsmParsers();
  InitializeAllAsmPrinters();

  // Obtain filehandle to destination file
  const auto filename{tmp_src.c_str()};
  std::error_code err_code{};
  raw_fd_ostream dest{filename, err_code, sys::fs::OF_None};

  if(err_code) {
    errs() << "Could not open file: " << err_code.message();
  }

  // Resolve target:
  const auto target_str{m_module->getTargetTriple()};
  std::string err;
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
  // traverse(ast);
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
