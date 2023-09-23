#include "llvm_backend.hpp"

// STL Includes:
#include <vector>

// Library Includes:
#include <llvm/IR/LegacyPassManager.h>
// #include <llvm/IR/PassManager.h>
#include <llvm/IR/Verifier.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Support/CodeGen.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Target/TargetMachine.h>

// Includes:
#include "../../ast/node/include.hpp"


// Macros:
#define STUB(t_type)                                            \
  auto LlvmBackend::visit([[maybe_unused]] t_type* t_ptr)->void \
  {}

// Using Statements:
using namespace backend::llvm_backend;
using namespace ast::visitor;
using namespace ast::node;
using namespace ast::node::control;
using namespace ast::node::functions;
using namespace ast::node::lvalue;
using namespace ast::node::operators;
using namespace ast::node::packaging;
using namespace ast::node::rvalue;
using namespace ast::node::typing;
using namespace ast::node::node_traits;

// Methods:
LlvmBackend::LlvmBackend()
  : m_context{std::make_shared<llvm::LLVMContext>()},
    m_builder{std::make_shared<llvm::IRBuilder<>>(*m_context)},
    m_module{std::make_shared<llvm::Module>("Module", *m_context)}
{}

auto LlvmBackend::visit(If* t_if) -> void
{
  using namespace llvm;

  APInt val{32, 0, true}; // TODO: This should be computed

  Value* condv{ConstantInt::get(*m_context, val)};
  // condv = m_builder->CreateFCmpONE(
  //   condv, ConstantInt::get(*m_context, APInt(32, 0, true)), "cond");

  auto* then{BasicBlock::Create(*m_context, "then")};
  auto* alt{BasicBlock::Create(*m_context, "alt")};

  m_builder->CreateCondBr(condv, then, alt);
}

STUB(Loop)
STUB(Continue)
STUB(Break)

auto LlvmBackend::visit(Return* t_ret) -> void
{
  using namespace llvm;

  APInt ret_val{32, 0, true};

  m_builder->CreateRet(ConstantInt::get(*m_context, ret_val));
}

// Functions:
auto LlvmBackend::visit(Function* t_fn) -> void
{
  using namespace llvm;

  auto params{std::vector<llvm::Type*>()};
  auto* fn_type{
    FunctionType::get(IntegerType::getInt32Ty(*m_context), params, false)};

  auto* fn{llvm::Function::Create(fn_type, llvm::Function::ExternalLinkage,
                                  t_fn->identifier(), m_module.get())};
  auto* body{llvm::BasicBlock::Create(*m_context, "entry", fn)};
  m_builder->SetInsertPoint(body);

  // Codegen for the body
  t_fn->body()->accept(this);

  llvm::verifyFunction(*fn);
}

STUB(FunctionCall)
STUB(ReturnType)
STUB(Const)
STUB(Let)
STUB(Variable)
STUB(Arithmetic)
STUB(Assignment)
STUB(Comparison)
STUB(Increment)
STUB(Decrement)
STUB(UnaryPrefix)
STUB(Not)
STUB(And)
STUB(Or)
STUB(Ternary)
STUB(Import)
STUB(ModuleDecl)
STUB(Float)
STUB(Integer)
STUB(String)
STUB(Boolean)
STUB(MethodDecl)
STUB(Interface)
STUB(MemberDecl)
STUB(Struct)
STUB(DefBlock)
STUB(DotExpr)

// Misc:
auto LlvmBackend::visit(List* t_list) -> void
{
  for(NodePtr& node : *t_list) {
    node->accept(this);
  }
}

STUB(Nil);

// Util:
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

auto LlvmBackend::compile(const fs::path t_path) -> void
{
  using namespace llvm;
  using namespace llvm::sys::fs;

  configure_target();

  // Obtain filehandle to destination file
  const auto filename{t_path.c_str()};
  std::error_code err_code;
  raw_fd_ostream dest{filename, err_code, sys::fs::OF_None};

  if(err_code) {
    errs() << "Could not open file: " << err_code.message();
  }

  // Initialize all target stuff:
  InitializeAllTargetInfos();
  InitializeAllTargets();
  InitializeAllTargetMCs();
  InitializeAllAsmParsers();
  InitializeAllAsmPrinters();

  // Resolve target:
  const auto target_str{m_module->getTargetTriple()};
  std::string err;
  auto target{TargetRegistry::lookupTarget(target_str, err)};
  if(!target) {
    errs() << err << '\n';
    // return 1;
    return; // TODO: Fix
  }

  // Set target machine:
  const auto cpu{"generic"};
  const auto Features{""};

  TargetOptions opt;
  Optional<Reloc::Model> reloc_model;
  auto target_machine{
    target->createTargetMachine(target_str, cpu, Features, opt, reloc_model)};

  // Write object file:
  legacy::PassManager pass;
  const auto fype{CGFT_ObjectFile};

  if(target_machine->addPassesToEmitFile(pass, dest, nullptr, fype)) {
    errs() << "target_machine can't emit a file of this type";
    // return 1;
    return; // TODO: Fix
  }

  pass.run(*m_module);
  dest.flush();

  // Close so that the permissions can be set
  dest.close();

  // Make object file executable:
  const perms permissions{others_write | all_read | all_exe};
  err_code = setPermissions(t_path.c_str(), permissions);

  errs() << err_code.message() << " Done...\n";

  if(err_code) {
    errs() << "Could not change file permissions: " << err_code.message();
    return;
  }
}
