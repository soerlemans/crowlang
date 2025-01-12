#include "python_backend.hpp"

namespace codegen::cpp_backend::interop_backends {
auto PythonBackend::prologue() -> std::string
{
  std::stringstream ss;

  ss << "// Pybind Includes:\n";
  ss << "#include <pybind11/pybind11.h>\n\n";

  return ss.str();
}

auto PythonBackend::epilogue() -> std::string
{
  std::stringstream ss;

  return ss.str();
}
} // namespace codegen::cpp_backend::interop_backends
