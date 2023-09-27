#ifndef CROW_BACKEND_LLVM_BACKEND_PROLOGUE_GENERATOR_HPP
#define CROW_BACKEND_LLVM_BACKEND_PROLOGUE_GENERATOR_HPP

// STL Includes:
#include <memory>

// Library Includes:
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

// Includes:
#include "../../ast/visitor/node_visitor.hpp"


namespace backend::llvm_backend {
// Using statements:
using namespace ast;

// Aliases:
using ContextPtr = std::shared_ptr<llvm::LLVMContext>;
using IrBuilderPtr = std::shared_ptr<llvm::IRBuilder<>>;
using ModulePtr = std::shared_ptr<llvm::Module>;

// Clasess:
/*! This class is responsible for generating a prologue declarations of globals,
 * types and functions so that the code can be executed and ran in an order
 * independent way.
 */
class PrologueGenerator : public ast::visitor::NodeVisitor {
  private:
  IrBuilderPtr m_builder;
  ContextPtr m_context;

  // Function:
  auto visit(node::functions::Function* t_fn) -> void override;

  public:
  PrologueGenerator(IrBuilderPtr& t_builder, ContextPtr& t_context);

  virtual ~PrologueGenerator() = default;
};

} // namespace backend::llvm_backend

#endif // CROW_BACKEND_LLVM_BACKEND_PROLOGUE_GENERATOR_HPP
