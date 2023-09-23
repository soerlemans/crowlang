#include "llvm_ir_backend.hpp"

// STL Includes:
#include <vector>

// Library Includes:
#include <llvm/IR/Verifier.h>
#include <llvm/Support/raw_ostream.h>

// Includes:
#include "../../ast/node/include.hpp"


// Macros:
#define STUB(t_type)                                              \
  auto LlvmIrBackend::visit([[maybe_unused]] t_type* t_ptr)->void \
  {}

// Using Statements:
using namespace backend::llvm_ir;
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
LlvmIrBackend::LlvmIrBackend()
  : m_context{std::make_unique<llvm::LLVMContext>()},
    m_builder{std::make_unique<llvm::IRBuilder<>>(*m_context)},
    m_module{std::make_unique<llvm::Module>("Module", *m_context)}
{}

STUB(If)
STUB(Loop)
STUB(Continue)
STUB(Break)
STUB(Return)

// Functions:
auto LlvmIrBackend::visit(Function* t_fn) -> void
{
  using namespace llvm;

  auto* fn_type{FunctionType::get(IntegerType::getInt32Ty(*m_context),
                                  std::vector<llvm::Type*>(), false)};

  auto* fn{llvm::Function::Create(fn_type, llvm::Function::ExternalLinkage,
                                  t_fn->identifier(), m_module.get())};
  auto* body{llvm::BasicBlock::Create(*m_context, "entry", fn)};
  m_builder->SetInsertPoint(body);

  llvm::APInt retVal(32, (uint32_t)0, true);
  m_builder->CreateRet(llvm::ConstantInt::get(*m_context, retVal));
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
STUB(List)
STUB(Nil)

auto LlvmIrBackend::dump_ir(std::ostream& t_os) -> void
{
  std::string str;
  llvm::raw_string_ostream oss(str);

  m_module->print(oss, nullptr);

  t_os << str;
}
