#include "prologue_generator.hpp"

// Includes:
#include "../../ast/node/include.hpp"
#include "../../debug/log.hpp"

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
PrologueGenerator::PrologueGenerator(IrBuilderPtr& t_builder, ContextPtr& t_context)
  : m_builder{t_builder}, m_context{t_context}
{}

auto PrologueGenerator::visit(Function* t_fn) -> void
{
  using namespace llvm;

  // auto params{std::vector<llvm::Type*>()};
  // auto* fn_type{
  //   FunctionType::get(IntegerType::getInt32Ty(*m_context), params, false)};

  // auto* fn
  // {llvm::Function::Create(fn_type, llvm::Function::ExternalLinkage,
}
