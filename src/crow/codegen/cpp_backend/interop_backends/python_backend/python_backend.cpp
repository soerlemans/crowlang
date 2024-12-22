#include "python_backend.hpp"

namespace codegen::cpp_backend::interop_backends {
auto PythonBackend::prologue() -> std::string
{
  return {};
}

auto PythonBackend::epilogue() -> std::string
{
  return {};
}

auto PythonBackend::generate(NodePtr t_ast) -> std::string
{
  return {};
}
} // namespace codegen::cpp_backend::interop_backends
