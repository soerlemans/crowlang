#include "backend_interface.hpp"

// Absolute Includes:
#include "crow/codegen/cpp_backend/cpp_backend.hpp"
#include "crow/codegen/llvm_backend/llvm_backend.hpp"

namespace codegen {
auto select_backend(const BackendType t_selector) -> BackendPtr
{
  using cpp_backend::CppBackend;
  using llvm_backend::LlvmBackend;

  BackendPtr ptr{};

  switch(t_selector) {
    case BackendType::LLVM_BACKEND:
      ptr = std::make_unique<LlvmBackend>();
      break;

    case BackendType::CPP_BACKEND:
      ptr = std::make_unique<CppBackend>();
      break;

    default:
      // TODO: Throw
      break;
  }

  return ptr;
}
} // namespace codegen
