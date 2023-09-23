#ifndef CROW_CODEGEN_LLVM_CODEGEN_HPP
#define CROW_CODEGEN_LLVM_CODEGEN_HPP

// Includes:
#include "../../ast/node/include.hpp"
#include "../../ast/visitor/node_visitor.hpp"


namespace codegen::llvm {
class LlvmCodegen : public NodeVisitor {
  private:
  public:
	LlvmCodegen() = default;

  virtual auto visit(node::NodeInterface* t_node) -> void;

	~LlvmCodegen() override = default;
};
} // namespace codegen::llvm

#endif // CROW_CODEGEN_LLVM_CODEGEN_HPP
