#include "type2llvm.hpp"

// Absolute Includes:
#include "lib/stdexcept/stdexcept.hpp"

// Macros:
#define MATCH(t_key, t_value) \
  case NativeType::t_key:     \
    ptr = t_value;            \
    break

namespace codegen::llvm_backend {
auto native_type2llvm(LlvmContextPtr t_context, const NativeType t_type)
  -> llvm::Type*
{
  llvm::Type* ptr{nullptr};

  if(!t_context) {
    using lib::stdexcept::throw_unexpected_nullptr;

    throw_unexpected_nullptr(
      "For nativetype2llvm we received a nullptr for LLVM Context pointer.");
  }

  switch(t_type) {
    MATCH(VOID, llvm::Type::getVoidTy(*m_context));

    MATCH(INT, llvm::Type::getInt32Ty(*m_context));
    MATCH(I8, llvm::Type::getInt8Ty(*m_context));
    MATCH(I16, llvm::Type::getInt16Ty(*m_context));
    MATCH(I32, llvm::Type::getInt32Ty(*m_context));
    MATCH(I64, llvm::Type::getInt64Ty(*m_context));
    MATCH(ISIZE, llvm::Type::getInt32Ty(*m_context));

    // LLVM does not have unsigned types, it depends on the operation.
    MATCH(UINT, llvm::Type::getInt32Ty(*m_context));
    MATCH(U8, llvm::Type::getInt8Ty(*m_context));
    MATCH(U16, llvm::Type::getInt16Ty(*m_context));
    MATCH(U32, llvm::Type::getInt32Ty(*m_context));
    MATCH(U64, llvm::Type::getInt64Ty(*m_context));
    MATCH(USIZE, llvm::Type::getInt32Ty(*m_context));

    // LLVM does not have a bool type, use i1.
    MATCH(BOOL, llvm::Type::getInt1Ty(*m_context));

    default: {
      using lib::stdexcept::throw_invalid_argument;

      throw_invalid_argument(
        "Unhandled NativeType cant be converted to llvm::Type*.");
      break;
    }
  }

  return ptr;
}
} // namespace codegen::llvm_backend
