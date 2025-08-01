#ifndef CROW_CROW_CODEGEN_LLVM_BACKEND_TYPE2LLVM_HPP
#define CROW_CROW_CODEGEN_LLVM_BACKEND_TYPE2LLVM_HPP

// Library Includes:
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Type.h>


// Absolute Includes:
#include "crow/types/core/core.hpp"

namespace codegen::llvm_backend {
// Aliases:
using types::core::NativeType;

using LlvmContextPtr = std::shared_ptr<llvm::LLVMContext>;

auto native_type2llvm(LlvmContextPtr t_context, NativeType t_type)
  -> llvm::Type*;
} // namespace codegen::llvm_backend

#endif // CROW_CROW_CODEGEN_LLVM_BACKEND_TYPE2LLVM_HPP
