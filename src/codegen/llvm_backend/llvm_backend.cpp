#include "llvm_backend.hpp"

// STL Includes:
#include <iostream>
#include <optional>
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
#include "../../types.hpp"


// Macros:
#define STUB(t_type)                                           \
  auto LlvmBackend::visit([[maybe_unused]] t_type* t_ptr)->Any \
  {                                                            \
    return {};                                                 \
  }

// Using Statements:
using namespace codegen::llvm_backend;
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
auto LlvmBackend::get_value(node::NodePtr t_ptr) -> llvm::Value*
{
  using namespace llvm;

  Value* t_val{nullptr};

  auto any{t_ptr->accept(this)};
  if(any.has_value()) {
    try {
      t_val = std::any_cast<Value*>(any);
    } catch(const std::bad_any_cast& e) {
      // TODO: Error handling
      throw e; // For now just rethrow
    }
  }

  return t_val;
}

LlvmBackend::LlvmBackend()
  : m_context{std::make_shared<llvm::LLVMContext>()},
    m_builder{std::make_shared<llvm::IRBuilder<>>(*m_context)},
    m_module{std::make_shared<llvm::Module>("Module", *m_context)}
{}

// Control:
auto LlvmBackend::visit(If* t_if) -> Any
{
  using namespace llvm;

  llvm::Function* fn{m_builder->GetInsertBlock()->getParent()};


  // Generate branch selection logic
  auto* condv{get_value(t_if->condition())};
  auto* constant{ConstantInt::get(*m_context, APInt(8, 0, true))};
  condv = m_builder->CreateICmpNE(condv, constant, "cond");

  // Define blocks
  auto* then{BasicBlock::Create(*m_context, "then")};
  auto* alt{BasicBlock::Create(*m_context, "alt")};
  auto* merge{BasicBlock::Create(*m_context, "merge")};

  m_builder->CreateCondBr(condv, then, alt);

  const auto block{[&](auto* t_block, auto t_lambda) {
    fn->insert(fn->end(), t_block);
    m_builder->SetInsertPoint(t_block);

    t_lambda();

    m_builder->CreateBr(merge);
    t_block = m_builder->GetInsertBlock();
  }};

  block(then, [&] {
    t_if->then()->accept(this);
  });

  block(alt, [&] {
    t_if->alt()->accept(this);
  });

  fn->insert(fn->end(), merge);
  m_builder->SetInsertPoint(merge);
  auto* pn{
    m_builder->CreatePHI(llvm::Type::getDoubleTy(*m_context), 2, "iftmp")};

  // Figure this out?
  // pn->addIncoming(ThenV, ThenBB);
  // pn->addIncoming(ElseV, ElseBB);

  return {};
}

STUB(Loop)
STUB(Continue)
STUB(Break)

auto LlvmBackend::visit(Return* t_ret) -> Any
{
  using namespace llvm;

  auto* val{get_value(t_ret->expr())};
  m_builder->CreateRet(val);

  return {};
}

// Functions:
auto LlvmBackend::visit(Function* t_fn) -> Any
{
  using namespace llvm;

  auto params{std::vector<llvm::Type*>()};
  auto* fn_type{
    FunctionType::get(IntegerType::getInt32Ty(*m_context), params, false)};

  auto* fn{llvm::Function::Create(fn_type, llvm::Function::ExternalLinkage,
                                  t_fn->identifier(), m_module.get())};

  auto* body{BasicBlock::Create(*m_context, "entry", fn)};
  m_builder->SetInsertPoint(body);

  // Codegen for the body
  t_fn->body()->accept(this);

  llvm::verifyFunction(*fn);

  return {t_fn};
}

STUB(FunctionCall)
STUB(ReturnType)

// Lvalue:
STUB(Const)
STUB(Let)
STUB(Variable)

// Operators:
auto LlvmBackend::visit(Arithmetic* t_arith) -> Any
{
  using namespace llvm;

  Value* expr;
  auto* lhs{get_value(t_arith->left())};
  auto* rhs{get_value(t_arith->right())};

  switch(t_arith->op()) {
    case ArithmeticOp::MULTIPLY:
      expr = m_builder->CreateMul(lhs, rhs, "multmp");
      break;

    case ArithmeticOp::DIVIDE:
      expr = m_builder->CreateSDiv(lhs, rhs, "divtmp");
      break;

    case ArithmeticOp::MODULO:
      // expr = m_builder->CreateDiv(lhs, rhs, "modtmp");
      break;

    case ArithmeticOp::ADD:
      expr = m_builder->CreateAdd(lhs, rhs, "addtmp");
      break;

    case ArithmeticOp::SUBTRACT:
      expr = m_builder->CreateSub(lhs, rhs, "subtmp");
      break;

    default:
      throw; // TODO: Throw something
      break;
  }

  return std::make_any<Value*>(expr);
}

STUB(Assignment)
STUB(Comparison)
STUB(Increment)
STUB(Decrement)
STUB(UnaryPrefix)

// Logical:
STUB(Not)
STUB(And)
STUB(Or)
STUB(Ternary)

// Packaging:
STUB(Import)
STUB(ModuleDecl)

// RValue:
auto LlvmBackend::visit(Float* t_float) -> Any
{
  using namespace llvm;

  APFloat num{t_float->get()};
  auto* constant{ConstantFP::get(*m_context, num)};

  return std::make_any<Value*>(constant);
}

auto LlvmBackend::visit(Integer* t_int) -> Any
{
  using namespace llvm;

  const auto result{static_cast<u64>(t_int->get())};
  const APInt num{32, result, true};
  auto* constant{ConstantInt::get(*m_context, num)};

  return std::make_any<Value*>(constant);
}

// TODO: Implement
auto LlvmBackend::visit([[maybe_unused]] String* t_str) -> Any
{
  return {};
}

auto LlvmBackend::visit(Boolean* t_bool) -> Any
{
  using namespace llvm;

  const auto result{static_cast<u64>((t_bool->get()) ? 1 : 0)};
  const APInt num{8, result, false};
  auto* constant{ConstantInt::get(*m_context, num)};

  return std::make_any<Value*>(constant);
}

// Typing:
STUB(MethodDecl)
STUB(Interface)
STUB(MemberDecl)
STUB(Struct)
STUB(Impl)
STUB(DotExpr)

// Util:
auto LlvmBackend::configure_target() -> void
{
  const auto target{llvm::sys::getDefaultTargetTriple()};

  m_module->setTargetTriple(target);
}

auto LlvmBackend::codegen(NodePtr t_ast) -> void
{
  configure_target();

  traverse(t_ast);
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
  // InitializeAllTargetInfos();
  // InitializeAllTargets();
  // InitializeAllTargetMCs();
  // InitializeAllAsmParsers();
  // InitializeAllAsmPrinters();

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
  std::optional<Reloc::Model> reloc_model;
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
