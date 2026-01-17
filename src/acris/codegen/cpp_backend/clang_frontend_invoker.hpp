#ifndef ACRIS_ACRIS_CODEGEN_CPP_BACKEND_CLANG_FRONTEND_INVOKER_HPP
#define ACRIS_ACRIS_CODEGEN_CPP_BACKEND_CLANG_FRONTEND_INVOKER_HPP

// STL Includes:
#include <filesystem>
#include <sstream>

// Absolute Includes:
#include "lib/filesystem.hpp"

namespace codegen::cpp_backend {
// Aliases:
namespace fs = std::filesystem;

// Classes:
class ClangFrontendInvoker {
  private:
  std::stringstream m_compiler_flags;
  std::string m_out;

  public:
  ClangFrontendInvoker();

  auto add_flags(std::string_view t_str) -> void;
  auto set_out(std::string_view t_out) -> void;
  auto compile(const fs::path& t_source) -> void;

  virtual ~ClangFrontendInvoker() = default;
};
} // namespace codegen::cpp_backend

#endif // ACRIS_ACRIS_CODEGEN_CPP_BACKEND_CLANG_FRONTEND_INVOKER_HPP
