#ifndef CROW_CROW_CODEGEN_CPP_BACKEND_INTEROP_BACKENDS_PYTHON_BACKEND_PYTHON_BACKEND_HPP
#define CROW_CROW_CODEGEN_CPP_BACKEND_INTEROP_BACKENDS_PYTHON_BACKEND_PYTHON_BACKEND_HPP

// STL Includes:
#include <sstream>

// Relative Includes:
#include "../interop_backend_interface.hpp"

namespace codegen::cpp_backend::interop_backends {
/*!
 * Generate pythong bindings for use with pybind11.
 * TODO: Describe usage generate(), dont run on whole ast.
 */
class PythonBackend : public InteropBackendInterface {
  private:
  std::stringstream m_ss;

  public:
  PythonBackend() = default;

  auto prologue() -> std::string override;
  auto epilogue() -> std::string override;

  virtual ~PythonBackend() = default;
};
} // namespace codegen::cpp_backend::interop_backends

#endif // CROW_CROW_CODEGEN_CPP_BACKEND_INTEROP_BACKENDS_PYTHON_BACKEND_PYTHON_BACKEND_HPP
