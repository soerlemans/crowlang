#include "clang_frontend_invoker.hpp"

// STL Includes:
#include <iostream>
#include <optional>
#include <vector>

// Library Includes:
#include <clang/Basic/Diagnostic.h>
#include <clang/Basic/DiagnosticOptions.h>
#include <clang/Basic/FileManager.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Basic/TargetInfo.h>
#include <clang/Basic/TargetOptions.h>
#include <clang/CodeGen/CodeGenAction.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/CompilerInvocation.h>
#include <clang/Frontend/TextDiagnosticPrinter.h>
#include <clang/Lex/PreprocessorOptions.h>
#include <llvm/ADT/IntrusiveRefCntPtr.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/Orc/CompileUtils.h>
#include <llvm/ExecutionEngine/Orc/LLJIT.h>
#include <llvm/ExecutionEngine/SectionMemoryManager.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Module.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/DynamicLibrary.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/InitLLVM.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Transforms/Utils/Cloning.h>
#include <llvm/Transforms/Utils/CodeExtractor.h>

// Local Includes:
#include "../../debug/log.hpp"
#include "../../lib/types.hpp"

namespace codegen::cpp_backend {
// Protected Methods:
auto ClangFrontendInvoker::init_llvm() -> void
{}

// Public Methods:
auto ClangFrontendInvoker::object(const path& t_in, const path& t_out) -> void
{
  using namespace llvm;
  using namespace clang;

  // Do compiling magic, terrible code must refactor later.
  std::vector<const char*> args = {t_in.native().c_str(), "-o",
                                   t_out.native().c_str()};

  auto args_ref{args.data()};
  int argc{(int)args.size()};

  InitLLVM llvm_init(argc, args_ref);

  // Initialize targets for compilation.
  InitializeAllTargets();
  InitializeAllTargetMCs();
  InitializeAllAsmPrinters();
  InitializeAllAsmParsers();

  CompilerInstance compiler{};
  DiagnosticOptions diagnosticOptions{};
  compiler.createDiagnostics();

  CompilerInvocation& invocation{compiler.getInvocation()};
  CompilerInvocation::CreateFromArgs(invocation, args,
                                     compiler.getDiagnostics());

  const auto targetOptions{std::make_shared<clang::TargetOptions>()};
  targetOptions->Triple = llvm::sys::getDefaultTargetTriple();

  TargetInfo* targetInfo{
    TargetInfo::CreateTargetInfo(compiler.getDiagnostics(), targetOptions)};
  compiler.setTarget(targetInfo);

  compiler.createFileManager();
  compiler.createSourceManager(compiler.getFileManager());

  compiler.createPreprocessor(TU_Complete);
  compiler.getPreprocessorOpts().UsePredefines = true;

  compiler.createASTContext();

  CodeGenAction* action{new EmitObjAction()};
  if(!compiler.ExecuteAction(*action)) {
    DBG_CRITICAL("Compilation failed!");

    // TODO: Throw.
  } else {
    DBG_CRITICAL("Compilation succeeded!");
  }
}

auto ClangFrontendInvoker::link(const path& t_in, const path& t_out) -> void
{
  using namespace llvm;
  using namespace clang;

  // Linking:
  /*
   LLVMContext context{};
  SMDiagnostic err{};
  auto module_{parseIRFile(t_in.native(), err, context)};
  if(!module_) {
    // DBG_CRITICAL("Error parsing object file: ", err.getMessage())
    return;
  }

  std::string error{};
  const auto targetOptions{std::make_shared<clang::TargetOptions>()};
  targetOptions->Triple = llvm::sys::getDefaultTargetTriple();

  auto target{TargetRegistry::lookupTarget(targetOptions->Triple, error)};
  if(!target) {
    DBG_CRITICAL("Error looking up target: ", error);
    return;
  }

  TargetMachine* targetMachine{
    target->createTargetMachine(targetOptions->Triple, "generic", "",
                                llvm::TargetOptions{}, llvm::Reloc::PIC_)};
  if(!targetMachine) {
    DBG_CRITICAL("Error creating target machine.");
    return;
  }

  llvm::legacy::PassManager pass{};
  auto fileType{CGFT_ObjectFile};
  std::error_code ec{};
  raw_fd_ostream dest(t_out.native(), ec, sys::fs::OF_None);
  if(ec) {
    // DBG_CRITICAL("Could not open output file: ", ec.message());
    return;
  }

  if(targetMachine->addPassesToEmitFile(pass, dest, nullptr, fileType)) {
    DBG_CRITICAL("The target machine cannot emit a file of this type.");
    return;
  }

  pass.run(*module_);
  dest.flush();

  DBG_INFO("Linking succeeded, executable written to ", t_out);
  */
}
} // namespace codegen::cpp_backend
