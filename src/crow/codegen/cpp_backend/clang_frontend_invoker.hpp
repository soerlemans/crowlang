#ifndef CROW_CROW_CODEGEN_CPP_BACKEND_CLANG_FRONTEND_INVOKER_HPP
#define CROW_CROW_CODEGEN_CPP_BACKEND_CLANG_FRONTEND_INVOKER_HPP

// STL Includes:
#include <filesystem>

// Absolute Includes:
#include "lib/filesystem.hpp"

namespace codegen::cpp_backend {
// Using Declarations:
using std::filesystem::path;

// Classes:
class ClangFrontendInvoker {
  public:
  ClangFrontendInvoker() = default;

  auto compile(const path& t_filepath) -> void;

  virtual ~ClangFrontendInvoker() = default;
};
} // namespace codegen::cpp_backend

#endif // CROW_CROW_CODEGEN_CPP_BACKEND_CLANG_FRONTEND_INVOKER_HPP
