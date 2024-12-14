#include "clang_frontend_invoker.hpp"

// STL Includes:
#include <cstdlib>
#include <iostream>
#include <memory>
#include <optional>
#include <sstream>
#include <vector>

// Library Includes:
#include <clang/Basic/TargetInfo.h>
#include <clang/Basic/TargetOptions.h>
#include <clang/CodeGen/CodeGenAction.h>
#include <clang/Driver/Driver.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/CompilerInvocation.h>
#include <clang/FrontendTool/Utils.h>
#include <clang/Lex/PreprocessorOptions.h>
#include <lld/Common/Driver.h>
#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/FileUtilities.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/InitLLVM.h>
#include <llvm/Support/Path.h>
#include <llvm/Support/Program.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Target/TargetMachine.h>

// Local Includes:
#include "crow/debug/log.hpp"
#include "lib/types.hpp"

// Check if drivers exist.
LLD_HAS_DRIVER(coff)
LLD_HAS_DRIVER(elf)
LLD_HAS_DRIVER(mingw)
LLD_HAS_DRIVER(macho)
LLD_HAS_DRIVER(wasm)

namespace codegen::cpp_backend {
// Protected Methods:
auto ClangFrontendInvoker::init_llvm_targets() -> void
{
  using namespace llvm;

  // Initialize all LLVM targets for compilation.
  InitializeAllTargets();
  InitializeAllTargetMCs();
  InitializeAllAsmPrinters();
  InitializeAllAsmParsers();
}

// Public Methods:
// TODO: Refactor.
auto ClangFrontendInvoker::compile(const path &t_filepath) -> void
{
  using namespace llvm;
  using namespace lld;
  using namespace clang;

  // TODO: Get the clang frontend integration to work.
  const auto stem{t_filepath.stem()};

  const auto tmp_base{t_filepath.parent_path() / stem};
  auto tmp_obj{tmp_base};
  tmp_obj += ".o";

  auto binary{stem};
  binary += ".out";

  const auto source_str{t_filepath.native()};
  const auto binary_str{binary.native()};

  // Logging:
  DBG_INFO("tmp_obj: ", tmp_obj);
  DBG_INFO("binary: ", binary);

  // Print generated code (lazy implementation).
#ifdef DEBUG
  DBG_PRINTLN("# C++ codegeneration:");

  const auto cmd_cat{std::format("clang-format --style=Google < {}", source_str)};
  std::system(cmd_cat.c_str());

  DBG_PRINTLN();
#endif // DEBUG

  DBG_PRINTLN("# Clang Compilation:");

  // TODO: Add -O2 flag on release and reldebug builds (not on debug).
  // FIXME: This is a temporary workaround till the programmatic approach works.

  const auto flags{"-g -ggdb -std=c++23"};
  const auto cmd{std::format("g++ {} {} -o {}", source_str, flags, binary_str)};
  const auto status_code{std::system(cmd.c_str())};

  if(status_code == 0) {
    DBG_NOTICE("Binary was generated!: ", binary);
  } else {
    // TODO: Throw an exception.
  }

  // TODO: Fix ugly Clang code.
  /*
  // Do compiling magic, terrible code must refactor later.
  std::vector<const char *> args = {tmp_src.native().c_str(), "-o",
                                    binary.native().c_str()};

  auto args_ref{args.data()};
  int argc{(int)args.size()};

  InitLLVM init(argc, args_ref);
  cl::ParseCommandLineOptions(argc, args_ref, "LLVM and LLD linker\n");

  init_llvm_targets();

  // Step 1: Set up the compiler instance
  CompilerInstance compiler;
  DiagnosticOptions diagnosticOptions;
  compiler.createDiagnostics();

  CompilerInvocation &invocation = compiler.getInvocation();
  std::vector<const char *> args2 = {tmp_src.native().c_str()};
  CompilerInvocation::CreateFromArgs(invocation, args2,
                                     compiler.getDiagnostics());

  auto targetOptions = std::make_shared<clang::TargetOptions>();
  targetOptions->Triple = sys::getDefaultTargetTriple();

  TargetInfo *targetInfo =
    TargetInfo::CreateTargetInfo(compiler.getDiagnostics(), targetOptions);
  compiler.setTarget(targetInfo);

  compiler.createFileManager();
  compiler.createSourceManager(compiler.getFileManager());

  compiler.createPreprocessor(TU_Complete);
  compiler.getPreprocessorOpts().UsePredefines = true;

  compiler.createASTContext();

  CodeGenAction *action = new EmitObjAction();
  if(!compiler.ExecuteAction(*action)) {
    errs() << "Compilation failed!\n";
    return;
  }

  // Step 2: Retrieve the object file
  LLVMContext context;
  std::unique_ptr<llvm::Module> module_ = action->takeModule();
  if(!module_) {
    errs() << "Error generating object file\n";
    return;
  }

  legacy::PassManager pass;
  std::error_code EC;
  raw_fd_ostream dest(tmp_obj.native(), EC, sys::fs::OF_None);
  if(EC) {
    errs() << "Could not open output file: " << EC.message() << "\n";
    return;
  }

  std::string error;
  auto target{TargetRegistry::lookupTarget(targetOptions->Triple, error)};
  if(!target) {
    errs() << "Error looking up target: " << error << "\n";
    return;
  }

  auto targetMachine = target->createTargetMachine(
    targetOptions->Triple, "generic", "", llvm::TargetOptions{}, std::nullopt,
    std::nullopt, CodeGenOpt::Default);
  if(!targetMachine) {
    errs() << "Error creating target machine\n";
    return;
  }

  if(targetMachine->addPassesToEmitFile(pass, dest, nullptr, CGFT_ObjectFile)) {
    errs() << "The target machine cannot emit a file of this type\n";
    return;
  }

  pass.run(*module_);
  dest.flush();

  // std::vector<const char *> lldArgs = {"ld.lld", tmp_obj.native().c_str(),
  // "-o",
  //                                      binary.native().c_str()};
  // lld::Result result{lld::lldMain(lldArgs, outs() errs(), LLD_ALL_DRIVERS)};
  // if(result.retCode) {
  //   errs() << "Linking failed!\n";
  //   return;
  // }

  outs() << "Compilation and linking succeeded!\n";
  */
}
} // namespace codegen::cpp_backend
