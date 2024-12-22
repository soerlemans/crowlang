#ifndef PYTHON_BACKEND_HPP
#define PYTHON_BACKEND_HPP

// Relative Includes:
#include "../interop_backend_interface.hpp"

namespace codegen::cpp_backend::interop_backends::python_backend {
class PythonBackend : public InteropBackendInterface {
  public:
  PythonBackend() = default;
  virtual ~PythonBackend() = default;
};
} // namespace codegen::cpp_backend::interop_backends::python_backend

#endif // PYTHON_BACKEND_HPP
