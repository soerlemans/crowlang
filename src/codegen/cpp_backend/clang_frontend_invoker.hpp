#ifndef CROW_CODEGEN_CPP_BACKEND_CLANG_FRONTEND_INVOKER_HPP
#define CROW_CODEGEN_CPP_BACKEND_CLANG_FRONTEND_INVOKER_HPP

// STL Includes:
#include <filesystem>
#include <memory>

// Library Includes:
// #include <clang/Basic/TargetOptions.h>

// Includes:
#include "../../lib/filesystem.hpp"

namespace codegen::cpp_backend {
// Using Declarations:
using std::filesystem::path;

// Classes:
class ClangFrontendInvoker {
  private:
  // std::shared_ptr<clang::> m_target_options;

  protected:
  auto init_llvm() -> void;

  public:
  ClangFrontendInvoker() = default;

  auto object(const path& t_in, const path& t_out) -> void;
  auto link(const path& t_in, const path& t_out) -> void;

  virtual ~ClangFrontendInvoker() = default;
};
} // namespace codegen::cpp_backend

#endif // CROW_CODEGEN_CPP_BACKEND_CLANG_FRONTEND_INVOKER_HPP
