#include "python_backend.hpp"

namespace codegen::cpp_backend::interop_backends::python_backend {
PythonBackend::PythonBackend(): m_ss{}, m_symbols{}
{
  // m_symbols.reserve();
}

auto PythonBackend::prologue() -> std::string
{
  std::stringstream ss;

  ss << "// Pybind Includes:\n";
  ss << "#include <pybind11/pybind11.h>\n\n";

  return ss.str();
}

auto PythonBackend::register_constant(const std::string_view t_id) -> void
{
  m_symbols.emplace_back(std::string{t_id}, ExportSymbolType::CONSTANT);
}

auto PythonBackend::register_variable(const std::string_view t_id) -> void
{
  m_symbols.emplace_back(std::string{t_id}, ExportSymbolType::VARIABLE);
}

auto PythonBackend::register_function(const std::string_view t_id) -> void
{
  m_symbols.emplace_back(std::string{t_id}, ExportSymbolType::FUNCTION);
}

auto PythonBackend::epilogue() -> std::string
{
  std::stringstream ss;

  ss << "PYBIND11_MODULE(crowlang_export, mod) {\n";
  ss << "namespace py = pybind11;\n";
  ss << R"(mod.doc() = "Crowlang program exported symbols.";)" << '\n';

  for(const auto& export_symbol : m_symbols) {
    const auto& [id, type] = export_symbol;
    switch(type) {
      case ExportSymbolType::CONSTANT:
        ss << std::format(R"(mod.attr("{}") = {})", id, id) << '\n';
        break;

      case ExportSymbolType::VARIABLE:
        ss << std::format(R"(mod.attr("{}") = &{})", id, id) << '\n';
        break;

      case ExportSymbolType::FUNCTION:
        ss << std::format(R"(mod.def("{}", &{}, "No documentation.");)", id, id)
           << '\n';
        break;

      default:
        // TODO: Error handle.
        break;
    }
  }

  ss << "}\n";

  return ss.str();
}
} // namespace codegen::cpp_backend::interop_backends::python_backend
