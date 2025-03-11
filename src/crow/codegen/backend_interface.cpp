#include "backend_interface.hpp"

// Relative Includes:
#include "cpp_backend/cpp_backend.hpp"
#include "cpp_backend/interop_backends/interop_backend_interface.hpp"
#include "cpp_backend/interop_backends/python_backend/python_backend.hpp"
#include "llvm_backend/llvm_backend.hpp"

namespace codegen {
auto select_backend(const BackendType t_selector) -> BackendPtr
{
  using cpp_backend::CppBackend;
  using llvm_backend::LlvmBackend;

  // Keep the names for C++ interop backends short.
  // FIXME: Use a factory function creating the cpp interop backends.
  namespace cpp2py_interop = cpp_backend::interop_backends::python_backend;

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
      auto cpp_backend{std::make_unique<CppBackend>()};

      cpp_backend->add_interop_backend(
        std::make_shared<cpp2py_interop::PythonBackend>());

      ptr = std::move(cpp_backend);
      break;
    }

    default:
      // TODO: Throw
      break;
  }

  return ptr;
}
} // namespace codegen
