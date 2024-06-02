#include "cpp_backend.hpp"

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
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/InitLLVM.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>

// Includes:
#include "../../ast/node/include_nodes.hpp"
#include "../../debug/log.hpp"
#include "../../lib/temporary_directory.hpp"
#include "../../lib/types.hpp"

namespace codegen::cpp_backend {
// Using Statements:
using namespace ast::visitor;

NODE_USING_ALL_NAMESPACES()

// Methods:
// Control:
auto CppBackend::visit(If* t_if) -> Any
{
  // const auto condition{traverse(t_if->init_expr())};

  return {};
}

auto CppBackend::visit(Loop* t_loop) -> Any
{
  return {};
}

AST_VISITOR_STUB(CppBackend, Continue)
AST_VISITOR_STUB(CppBackend, Break)

auto CppBackend::visit(Return* t_ret) -> Any
{
  write("{}", "return");
  traverse(t_ret->expr());
  write("{}", ";");

  return {};
}

// Functions:
auto CppBackend::visit([[maybe_unused]] Parameter* t_param) -> Any
{
  return {};
}

auto CppBackend::visit(Function* t_fn) -> Any
{
  const auto identifier{t_fn->identifier()};

  // TODO: Some day resolve the TypeVariant, for now every method returns int.
  const auto ret_type{"int"};

  write("auto {}() -> {}", identifier, ret_type);
  write("{}", "{");

  // Generate code for the body.
  traverse(t_fn->body());

  write("{}", "}");

  return {};
}

AST_VISITOR_STUB(CppBackend, Call)
AST_VISITOR_STUB(CppBackend, ReturnType)

// Lvalue:
AST_VISITOR_STUB(CppBackend, Let)

auto CppBackend::visit(Var* t_var) -> Any
{
  const auto identifier{t_var->identifier()};

  write("auto {}{{", identifier);
  traverse(t_var->init_expr());
  write("}};");

  return {};
}

auto CppBackend::visit(Variable* t_var) -> Any
{
  const auto identifier{t_var->identifier()};

  write("{}", identifier);

  return {};
}

// Operators:
auto CppBackend::visit(Arithmetic* t_arith) -> Any
{
  using ast::node::operators::ArithmeticOp;

  // TODO: Cleanup/Move else where!
  switch(t_arith->op()) {
    case ArithmeticOp::POWER:
      break;

    case ArithmeticOp::MULTIPLY:
      break;

    case ArithmeticOp::DIVIDE:
      break;
    case ArithmeticOp::MODULO:
      break;

    case ArithmeticOp::ADD:
      traverse(t_arith->left());
      write("{}", "+");
      traverse(t_arith->right());
      break;

    case ArithmeticOp::SUBTRACT:
      break;

    default:
      // TODO: Throw.
      break;
  }

  return {};
}

AST_VISITOR_STUB(CppBackend, Assignment)

auto CppBackend::visit(Comparison* t_comp) -> Any
{
  return {};
}

AST_VISITOR_STUB(CppBackend, Increment)
AST_VISITOR_STUB(CppBackend, Decrement)
AST_VISITOR_STUB(CppBackend, UnaryPrefix)

// Logical:
AST_VISITOR_STUB(CppBackend, Not)
AST_VISITOR_STUB(CppBackend, And)

auto CppBackend::visit([[maybe_unused]] Or* t_or) -> Any
{
  return {};
}

AST_VISITOR_STUB(CppBackend, Ternary)

// Packaging:
AST_VISITOR_STUB(CppBackend, Import)
AST_VISITOR_STUB(CppBackend, ModuleDecl)

// RValue:
auto CppBackend::visit(Float* t_float) -> Any
{

  return {};
}

auto CppBackend::visit(Integer* t_int) -> Any
{
  const auto value{t_int->get()};

  write("{}", value);


  return {};
}

// TODO: Implement
auto CppBackend::visit([[maybe_unused]] String* t_str) -> Any
{
  return {};
}

auto CppBackend::visit(Boolean* t_bool) -> Any
{
  return {};
}

// Typing:
AST_VISITOR_STUB(CppBackend, MethodDecl)
AST_VISITOR_STUB(CppBackend, Interface)
AST_VISITOR_STUB(CppBackend, MemberDecl)
AST_VISITOR_STUB(CppBackend, Struct)
AST_VISITOR_STUB(CppBackend, Impl)
AST_VISITOR_STUB(CppBackend, DotExpr)

// Util:
/*!
 * Transpile the AST to valid C++ code.
 * The C++ source is stored in a temporary directory.
 */
auto CppBackend::codegen(NodePtr t_ast) -> fs::path
{
  const auto tmp_dir{lib::temporary_directory()};
  const auto tmp_src{tmp_dir / "main.cpp"};

  DBG_INFO("tmp_dir: ", std::quoted(tmp_dir.native()));
  DBG_INFO("tmp_src: ", std::quoted(tmp_src.native()));

  m_ofs.open(tmp_src);

  traverse(t_ast);

  m_ofs.close();

  return tmp_src;
}

auto CppBackend::compile(NodePtr t_ast) -> void
{
  using namespace clang;

  // Generate C++ source file and return path.
  const auto path{codegen(t_ast)};

  // Do compiling magic, terrible code must refactor later.
  std::vector<const char*> args = {path.native().c_str()};
  auto args_ref{args.data()};
  int argc{args.size()};

  // llvm::InitLLVM llvm_init(argc, &(array.data()));
  llvm::InitLLVM llvm_init(argc, args_ref);

  // Initialize targets for code generation.
  llvm::InitializeAllTargets();
  llvm::InitializeAllTargetMCs();
  llvm::InitializeAllAsmPrinters();
  llvm::InitializeAllAsmParsers();

  CompilerInstance compiler;
  DiagnosticOptions diagnosticOptions;
  compiler.createDiagnostics();

  CompilerInvocation& invocation = compiler.getInvocation();
  CompilerInvocation::CreateFromArgs(invocation, args,
                                     compiler.getDiagnostics());

  std::shared_ptr<TargetOptions> targetOptions =
    std::make_shared<TargetOptions>();
  targetOptions->Triple = llvm::sys::getDefaultTargetTriple();
  TargetInfo* targetInfo =
    TargetInfo::CreateTargetInfo(compiler.getDiagnostics(), targetOptions);
  compiler.setTarget(targetInfo);

  compiler.createFileManager();
  compiler.createSourceManager(compiler.getFileManager());

  compiler.createPreprocessor(clang::TU_Complete);
  compiler.getPreprocessorOpts().UsePredefines = true;

  compiler.createASTContext();

  CodeGenAction* action = new EmitObjAction();
  if(!compiler.ExecuteAction(*action)) {
    DBG_CRITICAL("Compilation failed!");

    // TODO: Throw.
  } else {
    DBG_CRITICAL("Compilation succeeded!");
  }
}
} // namespace codegen::cpp_backend
