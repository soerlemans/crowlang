#ifndef CROW_CROW_CODEGEN_CPP_BACKEND_INTEROP_BACKENDS_PYTHON_BACKEND_PYTHON_BACKEND_HPP
#define CROW_CROW_CODEGEN_CPP_BACKEND_INTEROP_BACKENDS_PYTHON_BACKEND_PYTHON_BACKEND_HPP

// Relative Includes:
#include "../interop_backend_interface.hpp"

namespace codegen::cpp_backend::interop_backends {
class PythonBackend : public InteropBackendInterface {
  public:
  PythonBackend() = default;

  auto prologue() -> std::string override;
  auto epilogue() -> std::string override;
  auto generate(NodePtr t_ast) -> std::string override;

  virtual ~PythonBackend() = default;
};
} // namespace codegen::cpp_backend::interop_backends

#endif // CROW_CROW_CODEGEN_CPP_BACKEND_INTEROP_BACKENDS_PYTHON_BACKEND_PYTHON_BACKEND_HPP
