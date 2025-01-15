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
    case BackendType::LLVM_BACKEND: {
      ptr = std::make_unique<LlvmBackend>();
      break;
    }

    case BackendType::CPP_BACKEND: {
      // FIXME: For now we configure/create the CppBackend.
      // With all interop backends enabled.
      // Someday we should setup a more robust way that considers project.toml.
      // And CLI option settings, but for now just do it quick and dirty.
      ptr = std::make_unique<CppBackend>();
      break;
    }

    default:
      // TODO: Throw
      break;
  }

  return ptr;
}
} // namespace codegen
